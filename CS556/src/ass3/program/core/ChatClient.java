package ass3.program.core;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.text.MessageFormat;
import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import tools.config.ConfigLoader;
import ass3.program.core.ChatterContext.ContextKey;
import ass3.program.core.ClientStateMachine.CState;
import ass3.program.core.ServerStateMachine.SState;
import ass3.program.core.message.ExchSharedKeyRequest;
import ass3.program.core.message.ExchSharedKeyResponse;
import ass3.program.core.message.Message;
import ass3.program.core.message.PublicKeyRequest;
import ass3.program.core.message.PublicKeyResponse;
import ass3.program.core.message.Request;
import ass3.program.core.message.Response;
import ass3.program.core.message.SendTextRequest;
import ass3.program.core.message.SendTextResponse;

public class ChatClient {

	private Chatter parent;
	private String ip;
	private Socket socket;
	private ContextKey ck;

	private int port;

	private ServerStateMachine serverState;

	private ClientStateMachine clientState;

	private Logger logger = LoggerFactory.getLogger(getClass());

	public ChatClient(Chatter parent, String ip, int port) {
		super();
		this.parent = parent;
		this.ip = ip;
		this.port = port;
		this.serverState = new ServerStateMachine();
		this.clientState = new ClientStateMachine();
	}

	public ChatClient(Chatter parent, Socket socket) {
		this(parent, null, 0);
		InetSocketAddress remote = (InetSocketAddress) socket
				.getRemoteSocketAddress();
		ip = remote.getAddress().getHostAddress();
		port = remote.getPort();
		this.socket = socket;
	}

	public ContextKey getContextKey() {
		try {
			if (null == ck) {
				ck = new ContextKey(
						InetAddress.getLocalHost().getHostAddress(), this.ip);
			}
			return ck;
		} catch (UnknownHostException e) {
			throw new RuntimeException(e);
		}
	}

	public Chatter getParent() {
		return parent;
	}

	public String getIp() {
		return ip;
	}

	public int getPort() {
		return port;
	}

	protected void connect() {
		if (socket != null && socket.isConnected() && !socket.isClosed())
			return;
		try {
			socket = new Socket(ip, port);
			// Register server thread
			getParent().getServer().monitor(socket);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	protected void send(Message msg) {
		if (logger.isDebugEnabled()) {
			logger.debug(MessageFormat.format("Sending message {0}:{1}", msg
					.getClass().getName(), msg));
		}
		connect();
		try {
			// Update the IP info carried by the message
			if (msg instanceof Request) {
				msg.getCk().setB(getRemoteIp(socket));
			}
			if (msg instanceof Response) {
				// DO nothing cause the response get info from request
			}
			msg.prepare();
			new ObjectOutputStream(this.socket.getOutputStream())
					.writeObject(msg);
		} catch (SocketException e) {
			// Reconnect for socket exception
			try {
				socket.close();
			} catch (IOException e1) {
				logger.warn("Encounter exception on closing socket, ignore.",
						e1);
			}
			send(msg);
		} catch (IOException e) {
			logger.warn("Exception when send message", e);
			throw new RuntimeException();
		}
	}

	/**
	 * Process returned message
	 * 
	 * @param received
	 */
	protected void process(Message received) {
		if (logger.isDebugEnabled()) {
			logger.debug(MessageFormat.format("Processing message {0}:{1}",
					received.getClass().getName(), received));
		}
		if (received instanceof Request) {
			Request request = (Request) received;
			try {
				if (request instanceof PublicKeyRequest) {
					serverState.transit(SState.PUBLIC_KEY_SENT);
					clientState.transit(CState.PUBLIC_KEY_RECEIVED);
				}
				if (request instanceof ExchSharedKeyRequest) {
					serverState.transit(SState.SHARED_KEY_RECEIVED);
					clientState.transit(CState.SHARED_KEY_EXCHANGED);
				}
				if (request instanceof SendTextRequest) {
					// Do nothing now
					serverState.verify(SState.SHARED_KEY_RECEIVED);
				}
			} catch (IllegalStateException e) {
				send(request.respondError(Response.ERROR_NO_AUTHORIZED));
				return;
			}
			send(request.respond());
		}
		if (received instanceof Response) {
			// Update State Machine
			Response resp = (Response) received;
			try {
				if (resp.getError() != 0) {
					clientState.transit(CState.INIT);
				} else {
					if (received instanceof PublicKeyResponse) {
						clientState.transit(CState.PUBLIC_KEY_RECEIVED);
						serverState.transit(SState.PUBLIC_KEY_SENT);
					}
					if (received instanceof ExchSharedKeyResponse) {
						clientState.transit(CState.SHARED_KEY_EXCHANGED);
						serverState.transit(SState.SHARED_KEY_RECEIVED);
					}
				}
			} catch (IllegalStateException e) {
				// Illegal Transition, ignore the message
				return;
			}
			resp.process();
			// Release the clients that are waiting for the response
			responseReceived(received.getClass());
		}
		// Notify the listener
		MessageListener l = getListener();
		if (null != l) {
			l.messageReceived(new MessageEvent(this, received));
		}
	}

	private MessageListener listener;

	public MessageListener getListener() {
		return listener;
	}

	public void setListener(MessageListener listener) {
		this.listener = listener;
	}

	private Map<Class<?>, Object> monitors = new HashMap<Class<?>, Object>();

	private synchronized Object getLock(Class<?> clazz) {
		if (!monitors.containsKey(clazz)) {
			monitors.put(clazz, new Object());
		}
		return monitors.get(clazz);
	}

	private synchronized void clearLock(Class<?> clazz) {
		monitors.remove(clazz);
	}

	private void waitForResponse(Class<?> clazz) {
		Object lock = getLock(clazz);
		synchronized (lock) {
			try {
				lock.wait();
			} catch (InterruptedException e) {
				throw new RuntimeException(e);
			}
		}
	}

	private synchronized void responseReceived(Class<?> clazz) {
		Object lock = getLock(clazz);
		synchronized (lock) {
			lock.notify();
		}
		clearLock(clazz);
	}

	public void sendText(String message) {
		ContextKey ck = getContextKey();
		switch (clientState.getCurrentState()) {
		case INIT:
			// Allow the user to indicate bit-length
			send(new PublicKeyRequest(ck.getA(), ck.getB(),
					ConfigLoader.loadInt("key", "ELGAMAL_BITLENGTH")));
			waitForResponse(PublicKeyResponse.class);
			sendText(message);
			break;
		case PUBLIC_KEY_RECEIVED:
			// Allow user to indicate shared key
			send(new ExchSharedKeyRequest(ck.getA(), ck.getB(), ConfigLoader
					.load("key", "AES_KEY").getBytes()));
			waitForResponse(ExchSharedKeyResponse.class);
			sendText(message);
			break;
		case SHARED_KEY_EXCHANGED:
			send(new SendTextRequest(ck.getA(), ck.getB(), message));
			waitForResponse(SendTextResponse.class);
			// Check self state to determine whether need to resend
			if (!(clientState.getCurrentState() == CState.SHARED_KEY_EXCHANGED)) {
				// Error encountered, Resend
				sendText(message);
			}
			break;
		default:
			throw new IllegalStateException();
		}
	}

	public static final String getLocalIp(Socket socket) {
		return ((InetSocketAddress) socket.getLocalSocketAddress())
				.getAddress().getHostAddress();
	}

	public static final String getRemoteIp(Socket socket) {
		return ((InetSocketAddress) socket.getRemoteSocketAddress())
				.getAddress().getHostAddress();
	}

	/**
	 * Quit and releaser resource
	 */
	public void dispose() {
		ChatterContext.clear(ip);
		try {
			socket.close();
		} catch (Exception e) {
			LoggerFactory.getLogger(getClass()).warn(
					"Error while releasing client", e);
		}
	}
}
