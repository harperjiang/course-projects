package ass3.program.core.message;


import tools.elgamal.Cipher;
import tools.elgamal.ElgamalCipher;
import tools.elgamal.PrivateKey;
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

		Object key = ChatterContext.get(getCk().getB(),
				PublicKeyRequest.PUBLIC_KEY);
		byte[] shared = plainKey.getBytes();
		ChatterContext.put(getCk().getB(), SHARED_KEY, shared);
		try {
			Cipher elgamal = new ElgamalCipher();
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
		PrivateKey key = ChatterContext.get(getCk().getA(),
				PublicKeyRequest.PRIVATE_KEY);
		try {
			Cipher elgamal = new ElgamalCipher();
			elgamal.init(Cipher.DECRYPT_MODE, key);
			elgamal.update(encryptedKey);
			byte[] sharedKey = elgamal.doFinal();
			ChatterContext.put(getCk().getA(), SHARED_KEY, sharedKey);
			return new ExchSharedKeyResponse(getTo(), getFrom());
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

}
