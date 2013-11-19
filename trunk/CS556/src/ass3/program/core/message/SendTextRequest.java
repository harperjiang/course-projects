package ass3.program.core.message;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

import ass3.program.core.ChatterContext;

public class SendTextRequest extends Request {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1289859997855444176L;

	private byte[] payload;

	public SendTextRequest(String from, String to, String data) {
		super(from, to);
		// Encrypt the data
		try {
			Cipher aes = Cipher.getInstance("AES");
			byte[] shared = ChatterContext.get(getCk(),
					ExchSharedKeyRequest.SHARED_KEY);
			SecretKeySpec skeySpec = new SecretKeySpec(shared, "AES");
			aes.init(Cipher.ENCRYPT_MODE, skeySpec);
			aes.update(data.getBytes());
			aes.doFinal();
			// TODO Change this part to per-char encryption
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public byte[] getPayload() {
		return payload;
	}

	@Override
	public Message respond() {
		return null;
	}

}
