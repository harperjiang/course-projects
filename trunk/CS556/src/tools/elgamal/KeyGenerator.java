package tools.elgamal;

import java.math.BigInteger;
import java.util.Random;

public class KeyGenerator {

	private BigInteger p;

	private BigInteger g;

	private BigInteger a;

	private BigInteger b;

	public KeyGenerator(int bitlength) {
		Random random = new Random(System.currentTimeMillis());
		p = BigInteger.probablePrime(bitlength, random);
		// Use Random number to find a generator
		while (true) {
			BigInteger pg = BigInteger.probablePrime(bitlength, random).mod(p);
			if (!pg.equals(BigInteger.ONE)
					&& !pg.modPow(BigInteger.valueOf(2), p).equals(
							BigInteger.ONE)
					&& !pg.modPow(
							p.subtract(BigInteger.ONE).divide(
									BigInteger.valueOf(2)), p).equals(
							BigInteger.ONE)) {
				g = pg;
				break;
			}
		}
		a = BigInteger.probablePrime(bitlength - 1, random).mod(p);
		b = g.modPow(a, p);
	}

	public PublicKey getPublicKey() {
		return new PublicKey(p, g, b);
	}

	public PrivateKey getPrivateKey() {
		return new PrivateKey(p, g, a);
	}
}
