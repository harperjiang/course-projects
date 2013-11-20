package ass3.program.core.message;

public class SendTextResponse extends Response {

	/**
	 * 
	 */
	private static final long serialVersionUID = -7151945454936651111L;

	public SendTextResponse(String from, String to) {
		super(from, to);
	}

	@Override
	public void process() {

	}

}
