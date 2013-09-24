package ass2.project;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.math.BigInteger;

/**
 * 
 * 
 * 
 * 
 * @author harper
 * @since CS556 1.0
 * @version 1.0
 * 
 * 
 */
public class CharwiseRSA {

	private BigInteger n;

	private BigInteger e;

	private BigInteger d;

	public CharwiseRSA(BigInteger n, BigInteger e, BigInteger d) {
		this.n = n;
		this.e = e;
		this.d = d;
	}

	public void encrypt(InputStream input, OutputStream output)
			throws IOException {
		byte[] buffer = new byte[1000];
		int count = 0;
		while ((count = input.read(buffer)) != -1) {
			for (int i = 0; i < count; i++) {
				BigInteger result = encrypt(BigInteger
						.valueOf((long) buffer[i]));
				output.write(result.toString().getBytes());
				output.write(13);
				output.write(10);
			}
		}
	}

	public void decrypt(InputStream input, OutputStream output)
			throws IOException {
		String line = null;
		BufferedReader br = new BufferedReader(new InputStreamReader(input));
		while ((line = br.readLine()) != null) {
			BigInteger cipher = new BigInteger(line);
			BigInteger plain = decrypt(cipher);
			output.write(plain.intValue());
		}
	}

	protected BigInteger encrypt(BigInteger input) {
		return input.modPow(e, n);
	}

	protected BigInteger decrypt(BigInteger input) {
		return input.modPow(d, n);
	}

}
