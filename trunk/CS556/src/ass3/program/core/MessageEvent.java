package ass3.program.core;

import java.util.EventObject;

import ass3.program.core.message.Message;

public class MessageEvent extends EventObject {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1479881584043269862L;

	private Message content;

	public MessageEvent(Object source, Message content) {
		super(source);
		this.content = content;
	}

	public Message getContent() {
		return content;
	}

}
