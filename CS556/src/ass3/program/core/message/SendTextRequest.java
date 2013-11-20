package ass3.program.core.message;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

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

			ByteArrayOutputStream buffer = new ByteArrayOutputStream();
			for (byte b : data.getBytes("utf8")) {
				aes.update(new byte[] { b });
				buffer.write(aes.doFinal());
			}
			data = null;
			payload = buffer.toByteArray();
			// TODO Change this part to per-char encryption
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public String getText() {
		try {
			Cipher aes = Cipher.getInstance("AES");
			byte[] shared = ChatterContext.get(getCk().getA(),
					ExchSharedKeyRequest.SHARED_KEY);
			byte[] buffer = new byte[16];
			ByteArrayInputStream input = new ByteArrayInputStream(payload);
			ByteArrayOutputStream output = new ByteArrayOutputStream();
			SecretKeySpec skeySpec = new SecretKeySpec(shared, "AES");
			aes.init(Cipher.DECRYPT_MODE, skeySpec);
			while (input.read(buffer) > 0) {
				aes.update(buffer);
				output.write(aes.doFinal()[0]);
			}
			String result = new String(output.toByteArray(), "utf8");
			return result;
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public byte[] getPayload() {
		return payload;
	}

	@Override
	public Message respond() {
		return new SendTextResponse(getCk().getB(), getCk().getA());
	}

}
