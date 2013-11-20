package ass3.program.core;

import java.util.EventObject;

import ass3.program.core.message.Message;

public class ServerMessageEvent extends EventObject {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7602800009857324022L;

	private Message message;

	public ServerMessageEvent(ChatServer source, Message message) {
		super(source);
		this.message = message;
	}

	public Message getMessage() {
		return message;
	}

}
