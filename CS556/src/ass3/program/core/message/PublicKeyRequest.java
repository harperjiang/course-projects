package ass3.program.core.message;

import java.security.KeyPair;
import java.security.KeyPairGenerator;

import ass3.program.core.ChatterContext;

public class PublicKeyRequest extends Request {

	public static final String PRIVATE_KEY = "PrivateKey";

	private int bitLength;

	public PublicKeyRequest(int bitLength) {
		super();
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
			ChatterContext.put(PRIVATE_KEY, keyPair.getPrivate());
			return new PublicKeyResponse(keyPair.getPublic());
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}
