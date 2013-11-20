package ass3.program.core.message;

import tools.elgamal.KeyGenerator;
import ass3.program.core.ChatterContext;

public class PublicKeyRequest extends Request {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1257806048691099422L;

	public static final String PRIVATE_KEY = "PrivateKey";

	public static final String PUBLIC_KEY = "PublicKey";

	private int bitLength;

	public PublicKeyRequest(String from, String to, int bitLength) {
		super(from, to);
		this.bitLength = bitLength;
	}

	public int getBitLength() {
		return bitLength;
	}

	public Message respond() {
		// Generate Key Pair and respond the public key, the private key is
		// stored in the context
		KeyGenerator keyGen = new KeyGenerator(bitLength);
		ChatterContext.put(getCk(), PRIVATE_KEY, keyGen.getPrivateKey());
		return new PublicKeyResponse(getTo(), getFrom(), keyGen.getPublicKey());
	}
}
