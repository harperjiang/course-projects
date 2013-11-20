package ass3.program.core.message;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

import ass3.program.core.ChatterContext;

public class SendTextRequest extends Request {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1289859997855444176L;

	private String data;

	private byte[] payload;

	public SendTextRequest(String from, String to, String data) {
		super(from, to);
		this.data = data;
	}

	public void prepare() {
		// Encrypt the data
		try {
			Cipher aes = Cipher.getInstance("AES");
			byte[] shared = ChatterContext.get(getCk().getB(),
					ExchSharedKeyRequest.SHARED_KEY);
			SecretKeySpec skeySpec = new SecretKeySpec(shared, "AES");
			aes.init(Cipher.ENCRYPT_MODE, skeySpec);
			aes.update(data.getBytes());
			payload = aes.doFinal();
			data = null;
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
