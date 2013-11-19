package ass3.program.core;

import java.util.HashMap;
import java.util.Map;

public class Chatter implements ServerListener {

	public static final int PORT = 3423;

	private ChatServer server;

	private Map<String, ChatClient> clients;

	public Chatter() {
		super();
		server = new ChatServer(this, PORT);
		server.setListener(this);
		clients = new HashMap<String, ChatClient>();
	}

	public void send(String target, String message) {
		// Make sure that we have a client to the target
		if (!clients.containsKey(target)) {
			ChatClient client = new ChatClient(this, target, PORT);
			clients.put(target, client);
		}
		ChatClient client = clients.get(target);
		client.sendText(message);
	}

	@Override
	public void messageReceived(ServerMessageEvent event) {
		// Look for the corresponding client
		ChatClient client = clients.get(event.getMessage().getFrom());
		if (null != client) {
			// Discard the message if no client can be found
			client.process(event.getMessage());
		}
	}
}
