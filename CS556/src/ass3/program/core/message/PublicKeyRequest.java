package ass3.program.core.message;

import java.security.KeyPair;
import java.security.KeyPairGenerator;

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
		try {
			KeyPairGenerator keyGen = KeyPairGenerator.getInstance("ElGamal",
					"BC");
			KeyPair keyPair = keyGen.generateKeyPair();
			ChatterContext.put(getCk(), PRIVATE_KEY, keyPair.getPrivate());
			return new PublicKeyResponse(getTo(), getFrom(),
					keyPair.getPublic());
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}
