package ass3.program.core.message;

import java.io.Serializable;

import ass3.program.core.ChatterContext.ContextKey;

public abstract class Message implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6339908857519182439L;

	private ContextKey ck;

	public Message(String from, String to) {
		super();
		this.ck = new ContextKey(from, to);
	}

	public String getFrom() {
		return ck.getA();
	}

	public String getTo() {
		return ck.getB();
	}

	public ContextKey getCk() {
		return ck;
	}

}
