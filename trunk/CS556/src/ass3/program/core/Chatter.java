package ass3.program.core;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

import javax.swing.event.EventListenerList;

public class Chatter implements ServerListener, MessageListener {

	public static final int PORT = 3423;

	private ChatServer server;

	private Map<String, ChatClient> clients;

	private Executor threadPool = Executors.newFixedThreadPool(5);

	public Chatter() {
		super();
		server = new ChatServer(this, PORT);
		server.setListener(this);
		clients = new HashMap<String, ChatClient>();
	}

	protected void registerClient(ChatClient client) {
		clients.put(client.getIp(), client);
		client.setListener(this);
	}

	public void send(String target, String message) {
		synchronized (clients) {
			// Make sure that we have a client to the target
			if (!clients.containsKey(target)) {
				ChatClient client = new ChatClient(this, target, PORT);
				registerClient(client);
			}
		}
		final ChatClient client = clients.get(target);
		threadPool.execute(new SendTextTask(client, message));
	}

	@Override
	public void messageReceived(ServerMessageEvent event) {
		// Look for the corresponding client
		String target = event.getMessage().getFrom();
		synchronized (clients) {
			if (!clients.containsKey(target)) {
				// Construct a new client if none is found
				ChatClient client = new ChatClient(this, event.getMessage()
						.getFrom(), PORT);
				registerClient(client);
			}
		}
		clients.get(target).process(event.getMessage());
	}

	@Override
	public void messageReceived(MessageEvent event) {
		for (MessageListener l : listeners.getListeners(MessageListener.class))
			l.messageReceived(event);
	}

	public void dropChatter(String target) {
		synchronized (clients) {
			ChatClient client = clients.get(target);
			clients.remove(target);
			if (null != client)
				client.dispose();
		}
	}

	public ChatServer getServer() {
		return server;
	}

	private EventListenerList listeners = new EventListenerList();

	public void addListener(MessageListener l) {
		listeners.add(MessageListener.class, l);
	}

	public void removeListener(MessageListener l) {
		listeners.remove(MessageListener.class, l);
	}

	protected static final class SendTextTask implements Runnable {

		private ChatClient client;

		private String text;

		public SendTextTask(ChatClient client, String text) {
			this.client = client;
			this.text = text;
		}

		public void run() {
			client.sendText(text);
		}
	}
}
