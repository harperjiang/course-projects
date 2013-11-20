package ass3.program.core.message;

import ass3.program.core.ChatterContext;

public class PublicKeyResponse extends Response {
	/**
	 * 
	 */
	private static final long serialVersionUID = 3693550271388882552L;

	private Object key;

	public PublicKeyResponse(String from, String to, Object publicKey) {
		super(from, to);
		this.key = publicKey;
	}

	public Object getKey() {
		return key;
	}

	@Override
	public void process() {
		ChatterContext.put(getCk(), PublicKeyRequest.PUBLIC_KEY, key);
	}

}
