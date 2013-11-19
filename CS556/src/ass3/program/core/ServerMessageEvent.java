package ass3.program.core;

import java.util.EventObject;

import ass3.program.core.message.Request;

public class ServerMessageEvent extends EventObject {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7602800009857324022L;

	private Request message;

	public ServerMessageEvent(ChatServer source, Request message) {
		super(source);
		this.message = message;
	}

	public Request getMessage() {
		return message;
	}

}
