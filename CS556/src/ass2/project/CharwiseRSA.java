package ass2.project;

import java.io.InputStream;
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

	public CharwiseRSA(BigInteger p, BigInteger q, BigInteger e) {
		// First calculate d
		BigInteger phi = p.subtract(BigInteger.ONE).multiply(
				q.subtract(BigInteger.ONE));
		
	}

	public void encrypt(InputStream input, OutputStream output) {

	}

	public void decrypt(InputStream input, OutputStream output) {

	}
}
