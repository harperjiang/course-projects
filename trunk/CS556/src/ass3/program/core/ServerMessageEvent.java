package ass3.program.core;

import java.util.EventObject;

import ass3.program.core.message.Request;

public class ServerMessageEvent extends EventObject {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7602800009857324022L;

	private String clientId;

	private Request command;

	public ServerMessageEvent(ChatServer source, String clientId, Request command) {
		super(source);
		this.clientId = clientId;
		this.command = command;
	}

	public String getClientId() {
		return clientId;
	}

	public Request getCommand() {
		return command;
	}

}
