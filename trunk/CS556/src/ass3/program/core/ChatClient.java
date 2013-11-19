package ass3.program.core;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

import ass3.program.core.ChatterContext.ContextKey;
import ass3.program.core.message.ExchSharedKeyRequest;
import ass3.program.core.message.Message;
import ass3.program.core.message.PublicKeyRequest;
import ass3.program.core.message.Response;
import ass3.program.core.message.SendTextRequest;

public class ChatClient {

	private Chatter parent;
	private String ip;
	private Socket socket;

	private int port;

	private ClientStateMachine stateMachine;

	public ChatClient(Chatter parent, String ip, int port) {
		super();
		this.parent = parent;
		this.ip = ip;
		this.port = port;
		this.stateMachine = new ClientStateMachine();
	}

	public ContextKey getContextKey() {
		try {
			return new ContextKey(InetAddress.getLocalHost().getHostAddress(),
					this.ip);
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

	protected void send(Message msg) {
		connect();
		// Process returned message
		try {
			new ObjectOutputStream(this.socket.getOutputStream())
					.writeObject(msg);
		} catch (IOException e) {
			Logger.getLogger(getClass().getSimpleName()).log(Level.WARNING,
					"Exception when send message", e);
			throw new RuntimeException();
		}
	}

	protected void process(Message received) {
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
