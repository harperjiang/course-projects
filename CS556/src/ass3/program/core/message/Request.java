package ass3.program.core.message;

public abstract class Request extends Message {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6970530366639945607L;

	public Request(String from, String to) {
		super(from, to);
	}

	public abstract Message respond();
}
