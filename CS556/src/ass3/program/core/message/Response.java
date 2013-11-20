package ass3.program.core.message;

public abstract class Response extends Message {
	/**
	 * 
	 */
	private static final long serialVersionUID = 5856020389601118808L;

	public static final int ERROR_NO_AUTHORIZED = 1;

	private int error;

	public Response(String from, String to) {
		super(from, to);
	}

	public int getError() {
		return error;
	}

	public void setError(int error) {
		this.error = error;
	}

	public abstract void process();
}
