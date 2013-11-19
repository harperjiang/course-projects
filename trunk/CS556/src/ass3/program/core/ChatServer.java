package ass3.program.core;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.logging.Level;
import java.util.logging.Logger;

import ass3.program.core.message.Request;

public class ChatServer {

	private Chatter parent;

	private int port;

	private ServerListener listener;

	public ChatServer(Chatter parent, int port) {
		super();
		this.parent = parent;
		this.port = port;
		new Thread(new Runnable() {
			public void run() {
				listen();
			}
		}).start();
	}

	public Chatter getParent() {
		return parent;
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
			try {
				while (!socket.isClosed()
						&& (socket.getInputStream().available() != 0)) {
					try {
						Request request = (Request) new ObjectInputStream(
								socket.getInputStream()).readObject();
						if (ssm.transit(request)) { // Discard invalid message
							listener.messageReceived(new ServerMessageEvent(
									ChatServer.this,
									((InetSocketAddress) socket
											.getRemoteSocketAddress())
											.getAddress().toString(), request));
						}
					} catch (SocketException e) {
						if (socket != null && !socket.isClosed())
							socket.close();
						throw e;
					} catch (Exception e) {
						logger.log(Level.WARNING, "Error processing message", e);
					}
				}
			} catch (Exception e) {
				logger.log(Level.WARNING, "Error reading socket", e);
				if (e instanceof RuntimeException)
					throw (RuntimeException) e;
				throw new RuntimeException(e);
			}
		}
	}
}
