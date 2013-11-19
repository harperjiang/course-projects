package ass3.program.core.message;

import java.security.PrivateKey;
import java.security.PublicKey;

import javax.crypto.Cipher;

import ass3.program.core.ChatterContext;

public class ExchSharedKeyRequest extends Request {

	/**
	 * 
	 */
	private static final long serialVersionUID = 536691245716545230L;

	public static final String SHARED_KEY = "SharedKey";

	private byte[] encryptedKey;

	public ExchSharedKeyRequest(String from, String to, String plainKey) {
		super(from, to);

		PublicKey key = ChatterContext
				.get(getCk(), PublicKeyRequest.PUBLIC_KEY);
		byte[] shared = plainKey.getBytes();
		ChatterContext.put(getCk(), SHARED_KEY, shared);
		try {
			Cipher elgamal = Cipher.getInstance("ElGamal/None/NoPadding", "BC");
			elgamal.init(Cipher.ENCRYPT_MODE, key);
			elgamal.update(shared);
			this.encryptedKey = elgamal.doFinal();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	@Override
	public Message respond() {
		// Extract shared key from the encrypted message;
		PrivateKey key = ChatterContext.get(getCk(),
				PublicKeyRequest.PRIVATE_KEY);
		try {
			Cipher elgamal = Cipher.getInstance("ElGamal/None/NoPadding", "BC");
			elgamal.init(Cipher.DECRYPT_MODE, key);
			elgamal.update(encryptedKey);
			byte[] sharedKey = elgamal.doFinal();
			ChatterContext.put(getCk(), SHARED_KEY, sharedKey);
			return new ExchSharedKeyResponse(getTo(), getFrom());
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

}
