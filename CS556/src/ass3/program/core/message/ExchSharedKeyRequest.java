package ass3.program.core.message;

import java.security.PrivateKey;

import javax.crypto.Cipher;

import ass3.program.core.ChatterContext;

public class ExchSharedKeyRequest extends Request {

	public static final String SHARED_KEY = "SharedKey";

	private String encryptedKey;

	public ExchSharedKeyRequest(String encryptedKey) {
		this.encryptedKey = encryptedKey;
		
	}

	@Override
	public Message respond() {
		// Extract shared key from the encrypted message;
		PrivateKey key = ChatterContext.get(PublicKeyRequest.PRIVATE_KEY);
		try {
			Cipher elgamal = Cipher.getInstance("ElGamal/None/NoPadding", "BC");
			elgamal.init(Cipher.DECRYPT_MODE, key);
			elgamal.update(encryptedKey.getBytes());
			byte[] sharedKey = elgamal.doFinal();
			ChatterContext.put(SHARED_KEY, sharedKey);
			return new ExchSharedKeyResponse();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

}
