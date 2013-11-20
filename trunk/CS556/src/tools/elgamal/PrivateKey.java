package tools.elgamal;

import java.math.BigInteger;

public class PrivateKey implements Key {

	private BigInteger p;

	private BigInteger g;

	private BigInteger a;

	public PrivateKey(BigInteger p, BigInteger g, BigInteger a) {
		super();
		this.p = p;
		this.g = g;
		this.a = a;
	}

	public BigInteger getP() {
		return p;
	}

	public BigInteger getG() {
		return g;
	}

	public BigInteger getA() {
		return a;
	}

}
