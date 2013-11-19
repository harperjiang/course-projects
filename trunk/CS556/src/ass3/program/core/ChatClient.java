package ass3.program.core;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.text.MessageFormat;
import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import ass3.program.core.ChatterContext.ContextKey;
import ass3.program.core.ClientStateMachine.State;
import ass3.program.core.message.ExchSharedKeyRequest;
import ass3.program.core.message.ExchSharedKeyResponse;
import ass3.program.core.message.Message;
import ass3.program.core.message.PublicKeyRequest;
import ass3.program.core.message.PublicKeyResponse;
import ass3.program.core.message.Request;
import ass3.program.core.message.Response;
import ass3.program.core.message.SendTextRequest;

public class ChatClient {

	private Chatter parent;
	private String ip;
	private Socket socket;
	private ContextKey ck;

	private int port;

	private ClientStateMachine stateMachine;

	private Logger logger = LoggerFactory.getLogger(getClass());

	public ChatClient(Chatter parent, String ip, int port) {
		super();
		this.parent = parent;
		this.ip = ip;
		this.port = port;
		this.stateMachine = new ClientStateMachine();
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
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	protected void send(Request msg) {
		if (logger.isDebugEnabled()) {
			logger.debug(MessageFormat.format("Sending message {0}:{1}", msg
					.getClass().getName(), msg));
		}
		connect();
		try {
			msg.setCk(new ContextKey(getFromIp(socket), getToIp(socket)));
			msg.prepare();
			new ObjectOutputStream(this.socket.getOutputStream())
					.writeObject(msg);
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
		// Update State Machine
		try {
			if (received instanceof PublicKeyResponse) {
				stateMachine.transit(State.PUBLIC_KEY_RECEIVED);
			}
			if (received instanceof ExchSharedKeyResponse) {
				stateMachine.transit(State.SHARED_KEY_EXCHANGED);
			}
		} catch (IllegalStateException e) {
			// Illegal Transition, ignore the message
			return;
		}
		((Response) received).process();

		responseReceived(received.getClass());
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
		switch (stateMachine.getCurrentState()) {
		case INIT:
			// TODO Allow the user to indicate bit-length
			send(new PublicKeyRequest(ck.getA(), ck.getB(), 512));
			waitForResponse(PublicKeyResponse.class);
			sendText(message);
			break;
		case PUBLIC_KEY_RECEIVED:
			// TODO Allow user to indicate shared key
			send(new ExchSharedKeyRequest(ck.getA(), ck.getB(), "shared key"));
			waitForResponse(ExchSharedKeyResponse.class);
			sendText(message);
			break;
		case SHARED_KEY_EXCHANGED:
			send(new SendTextRequest(ck.getA(), ck.getB(), message));
			break;
		default:
			throw new IllegalStateException();
		}
	}

	public static final String getFromIp(Socket socket) {
		return socket.getInetAddress().getHostAddress();
	}

	public static final String getToIp(Socket socket) {
		return ((InetSocketAddress) socket.getRemoteSocketAddress())
				.getAddress().getHostAddress();
	}
}
