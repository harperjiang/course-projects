package ass3.program.core.message;

import java.security.PublicKey;

public class PublicKeyResponse extends Message {

	/**
	 * 
	 */
	private static final long serialVersionUID = 3693550271388882552L;
	
	private PublicKey key;

	public PublicKeyResponse(PublicKey publicKey) {
		this.key = publicKey;
	}

	public PublicKey getKey() {
		return key;
	}

}
