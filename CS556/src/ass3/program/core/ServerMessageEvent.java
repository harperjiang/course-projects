package ass3.program.core;

import java.util.EventObject;

import ass3.program.core.message.Request;

public class ServerMessageEvent extends EventObject {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7602800009857324022L;

	private String clientId;

	private Request message;

	public ServerMessageEvent(ChatServer source, String clientId,
			Request message) {
		super(source);
		this.clientId = clientId;
		this.message = message;
	}

	public String getClientId() {
		return clientId;
	}

	public Request getMessage() {
		return message;
	}

}
