package ass3.program.core.message;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

import ass3.program.core.ChatterContext;

public class SendStringRequest extends Request {

	private byte[] payload;

	public SendStringRequest(String data) {
		super();
		// Encrypt the data
		try {
			Cipher aes = Cipher.getInstance("AES");
			SecretKeySpec skeySpec = ChatterContext
					.get(ExchSharedKeyRequest.SHARED_KEY);
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
