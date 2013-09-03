package ass1.project.io;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import ass1.Cipher;

public class DecryptionInputStream extends InputStream {

	private byte[] content;

	private Cipher cipher;

	private InputStream inner;

	private int pointer;

	public DecryptionInputStream(InputStream input) {
		super();
		this.inner = input;
	}

	protected void buffer() throws IOException {
		if (content != null)
			return;
		if (cipher == null || inner == null) {
			throw new IllegalArgumentException();
		}
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		byte[] buffer = new byte[2000];
		int count = 0;
		while ((count = inner.read(buffer)) != -1) {
			bos.write(buffer, 0, count);
		}
		content = cipher.decrypt(bos.toByteArray());
		pointer = 0;
	}

	@Override
	public int read() throws IOException {
		buffer();
		if (pointer >= content.length)
			return -1;
		return content[pointer++];
	}

	@Override
	public int read(byte[] b, int off, int len) throws IOException {
		buffer();
		if (pointer >= content.length)
			return -1;
		int readlength = Math.min(len, content.length - pointer);
		System.arraycopy(content, pointer, b, off, readlength);
		pointer += readlength;
		return readlength;
	}

	public Cipher getCipher() {
		return cipher;
	}

	public void setCipher(Cipher cipher) {
		this.cipher = cipher;
	}

}
