package ass3.program.core;

import java.util.HashMap;
import java.util.Map;

import ass3.program.core.message.Message;

public class Chatter implements ServerListener {

	public static final int PORT = 3423;

	private ChatServer server;

	private Map<String, ChatClient> clients;

	public Chatter() {
		super();
		server = new ChatServer(PORT);
		server.setListener(this);
		clients = new HashMap<String, ChatClient>();
	}

	public void send(String target, Message message) {
		// Make sure that we have a client to the target
		if (!clients.containsKey(target)) {
			ChatClient client = new ChatClient(target, PORT);
			clients.put(target, client);
		}
		clients.get(target).send(message);
	}

	@Override
	public void commandReceived(ServerMessageEvent command) {

	}
}
