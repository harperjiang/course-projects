package ass3.program.core.message;

public abstract class Response extends Message {
	/**
	 * 
	 */
	private static final long serialVersionUID = 5856020389601118808L;

	public Response(String from, String to) {
		super(from, to);
	}

	public abstract void process();
}
