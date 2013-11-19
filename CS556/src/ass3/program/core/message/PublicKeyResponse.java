package ass3.program.core.message;

import java.security.PublicKey;

import ass3.program.core.ChatterContext;

public class PublicKeyResponse extends Response {
	/**
	 * 
	 */
	private static final long serialVersionUID = 3693550271388882552L;

	private PublicKey key;

	public PublicKeyResponse(String from, String to, PublicKey publicKey) {
		super(from, to);
		this.key = publicKey;
	}

	public PublicKey getKey() {
		return key;
	}

	@Override
	public void process() {
		ChatterContext.put(getCk(), PublicKeyRequest.PUBLIC_KEY, key);
	}

}
