package ass3.program.core;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.text.MessageFormat;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import ass3.program.core.message.Message;
import ass3.program.core.message.Request;
import ass3.program.core.message.Response;

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
				Socket clientSocket = serverSocket.accept();
				getParent().registerClient(
						new ChatClient(getParent(), clientSocket));
				monitor(clientSocket);
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

	public void monitor(Socket socket) {
		ServerThread thread = new ServerThread(socket);
		thread.start();
	}

	protected final class ServerThread extends Thread {

		private Socket socket;

		private Logger logger = LoggerFactory.getLogger(ServerThread.class);

		public ServerThread(Socket socket) {
			this.socket = socket;
		}

		public void run() {
			if (!socket.isConnected()) {
				logger.warn("The socket is not connected");
				return;
			}
			try {
				while (!socket.isClosed()) {
					try {
						while (socket.getInputStream().available() == 0) {
							Thread.sleep(500);
						}
						Message message = (Message) new ObjectInputStream(
								socket.getInputStream()).readObject();
						// Update the IP info carried by the message
						if (message instanceof Request) {
							message.getCk()
									.setA(ChatClient.getRemoteIp(socket));
						}
						if (message instanceof Response) {
							// Do nothing cause reponse get info from request
						}
						if (logger.isDebugEnabled()) {
							logger.debug(MessageFormat.format(
									"Received message {0}:{1}", message
											.getClass().getName(), message));
						}
						listener.messageReceived(new ServerMessageEvent(
								ChatServer.this, message));
					} catch (SocketException e) {
						if (socket != null && !socket.isClosed())
							socket.close();
						throw e;
					} catch (Exception e) {
						logger.warn("Error processing message", e);
					}
				}
			} catch (Exception e) {
				logger.warn("Error reading socket", e);
				if (e instanceof RuntimeException)
					throw (RuntimeException) e;
				throw new RuntimeException(e);
			}
		}
	}

}
