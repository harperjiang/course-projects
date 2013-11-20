package tools.elgamal;

import java.math.BigInteger;
import java.util.Random;

public class KeyGenerator {

	private BigInteger n;

	private BigInteger e;

	private BigInteger d;

	public KeyGenerator(int bitlength) {
		Random random = new Random(System.currentTimeMillis());
		BigInteger p = BigInteger.probablePrime(bitlength, random);
		BigInteger q = BigInteger.probablePrime(bitlength, random);
		n = p.multiply(q);
		// First calculate d
		e = BigInteger.probablePrime(bitlength, random);
		BigInteger phi = p.subtract(BigInteger.ONE).multiply(
				q.subtract(BigInteger.ONE));
		d = e.modInverse(phi);
	}

	public BigInteger getBase() {
		return n;
	}

	public BigInteger getPublicKey() {
		return e;
	}

	public BigInteger getPrivateKey() {
		return d;
	}

}
