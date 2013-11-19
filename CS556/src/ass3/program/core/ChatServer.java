package ass3.program.core;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.logging.Level;
import java.util.logging.Logger;

import ass3.program.core.message.Request;
import ass3.program.core.message.MessageParser;

public class ChatServer {

	private int port;

	private ServerListener listener;

	public ChatServer(int port) {
		super();
		this.port = port;
		listen();
	}

	public int getPort() {
		return port;
	}

	public ServerListener getListener() {
		return listener;
	}

	public void setListener(ServerListener listener) {
		this.listener = listener;
	}

	public void listen() {
		ServerSocket serverSocket = null;
		try {
			serverSocket = new ServerSocket(port);
			while (true) {
				Socket client = serverSocket.accept();
				ServerThread thread = new ServerThread(client,
						new ServerStateMachine());
				thread.start();
			}
		} catch (IOException e) {
			if (null != serverSocket)
				try {
					serverSocket.close();
				} catch (IOException ee) {
					throw new RuntimeException(ee);
				}
			throw new RuntimeException(e);
		}
	}

	protected final class ServerThread extends Thread {

		private Socket socket;

		private ServerStateMachine ssm;

		private Logger logger = Logger.getLogger(ServerThread.class
				.getSimpleName());

		public ServerThread(Socket socket, ServerStateMachine ssm) {
			this.socket = socket;
			this.ssm = ssm;
		}

		public void run() {
			if (!socket.isConnected()) {
				logger.log(Level.WARNING, "The socket is not connected");
				return;
			}
			while (!socket.isClosed()) {
				try {
					Request cmd = MessageParser.parse(socket.getInputStream());
					listener.commandReceived(new ServerMessageEvent(
							ChatServer.this, ((InetSocketAddress) socket
									.getRemoteSocketAddress()).getAddress()
									.toString(), cmd));
					ssm.transit(cmd);
				} catch (SocketException e) {
					try {
						if (socket != null && !socket.isClosed())
							socket.close();
					} catch (Exception e0) {
						throw new RuntimeException(e0);
					}
					throw new RuntimeException(e);
				} catch (Exception e) {
					logger.log(Level.WARNING, "Error processing message", e);
				}
			}
		}
	}
}
