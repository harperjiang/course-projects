package utils;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class IOUtils {

	public static void copy(InputStream in, OutputStream out)
			throws IOException {
		byte[] buffer = new byte[2000];
		int count = 0;
		while ((count = in.read(buffer)) != -1) {
			out.write(buffer, 0, count);
		}
	}
}
