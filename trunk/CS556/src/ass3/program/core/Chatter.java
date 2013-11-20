package ass3.program.core;

import java.util.HashMap;
import java.util.Map;

import javax.swing.event.EventListenerList;

public class Chatter implements ServerListener, MessageListener {

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
			client.setListener(this);
			clients.put(target, client);
		}
		ChatClient client = clients.get(target);
		client.sendText(message);
	}

	@Override
	public void messageReceived(ServerMessageEvent event) {
		// Look for the corresponding client
		ChatClient client = clients.get(event.getMessage().getFrom());
		if (null == client) {
			// Construct a new client if none is found
			client = new ChatClient(this, event.getMessage().getFrom(), PORT);
			clients.put(event.getMessage().getFrom(), client);
		}
		client.process(event.getMessage());
	}

	@Override
	public void messageReceived(MessageEvent event) {
		for (MessageListener l : listeners.getListeners(MessageListener.class))
			l.messageReceived(event);
	}

	private EventListenerList listeners = new EventListenerList();

	public void addListener(MessageListener l) {
		listeners.add(MessageListener.class, l);
	}

	public void removeListener(MessageListener l) {
		listeners.remove(MessageListener.class, l);
	}
}
