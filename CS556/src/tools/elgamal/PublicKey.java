package tools.elgamal;

import java.math.BigInteger;

public class PublicKey implements Key {

	private BigInteger p;

	private BigInteger g;

	private BigInteger b;

	public PublicKey(BigInteger p, BigInteger g, BigInteger b) {
		super();
		this.p = p;
		this.g = g;
		this.b = b;
	}

	public BigInteger getP() {
		return p;
	}

	public BigInteger getG() {
		return g;
	}

	public BigInteger getB() {
		return b;
	}

}
