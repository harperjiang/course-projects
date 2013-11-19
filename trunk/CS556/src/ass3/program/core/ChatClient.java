package ass3.program.core;

import java.io.IOException;
import java.net.Socket;

import ass3.program.core.message.Message;

public class ChatClient {

	private String ip;

	private int port;

	public ChatClient(String ip, int port) {
		super();
		this.ip = ip;
		this.port = port;
	}

	public String getIp() {
		return ip;
	}

	public int getPort() {
		return port;
	}

	protected void connect() {
		try {
			Socket socket = new Socket(ip, port);

		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public void send(Message message) {
		
	}

}
