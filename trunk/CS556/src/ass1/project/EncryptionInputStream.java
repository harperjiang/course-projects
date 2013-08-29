package ass1.project;

import java.io.IOException;
import java.io.InputStream;

public class EncryptionInputStream extends InputStream {

	private InputStream in;

	public EncryptionInputStream(InputStream in) {
		this.in = in;
	}

	@Override
	public int read() throws IOException {
		return 0;
	}

}
