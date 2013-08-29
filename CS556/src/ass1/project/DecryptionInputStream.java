package ass1.project;

import java.io.IOException;
import java.io.InputStream;

public class DecryptionInputStream extends InputStream {

	private InputStream in;

	public DecryptionInputStream(InputStream in) {
		this.in = in;
	}

	@Override
	public int read() throws IOException {
		// TODO Auto-generated method stub
		return 0;
	}

}
