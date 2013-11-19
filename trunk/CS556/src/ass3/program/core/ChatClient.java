package ass3.program.core;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.text.MessageFormat;
import java.util.logging.Level;
import java.util.logging.Logger;

import ass3.program.core.ChatterContext.ContextKey;
import ass3.program.core.message.ExchSharedKeyRequest;
import ass3.program.core.message.Message;
import ass3.program.core.message.PublicKeyRequest;
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

	private Logger logger = Logger.getLogger(getClass().getName());

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
		if (logger.isLoggable(Level.FINE)) {
			logger.fine(MessageFormat.format("Sending message {0}:{1}", msg
					.getClass().getName(), msg));
		}
		connect();
		// Process returned message
		try {
			msg.prepare();
			new ObjectOutputStream(this.socket.getOutputStream())
					.writeObject(msg);
		} catch (IOException e) {
			logger.log(Level.WARNING, "Exception when send message", e);
			throw new RuntimeException();
		}
	}

	protected void process(Message received) {
		if (logger.isLoggable(Level.FINE)) {
			logger.fine(MessageFormat.format("Processing message {0}:{1}",
					received.getClass().getName(), received));
		}
		((Response) received).process();
	}

	public void sendText(String message) {
		ContextKey ck = getContextKey();
		switch (stateMachine.getCurrentState()) {
		case INIT:
			// TODO Allow the user to indicate bit-length
			send(new PublicKeyRequest(ck.getA(), ck.getB(), 512));
			sendText(message);
			break;
		case PUBLIC_KEY_RECEIVED:
			// TODO Allow user to indicate shared key
			send(new ExchSharedKeyRequest(ck.getA(), ck.getB(), "shared key"));
			sendText(message);
			break;
		case SHARED_KEY_EXCHANGED:
			send(new SendTextRequest(ck.getA(), ck.getB(), message));
			break;
		default:
			throw new IllegalStateException();
		}
	}

}
