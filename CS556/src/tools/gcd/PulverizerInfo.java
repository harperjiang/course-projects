package tools.gcd;

import java.math.BigInteger;

public class PulverizerInfo {

	private BigInteger x1;

	private BigInteger y1;

	private BigInteger x2;

	private BigInteger y2;

	public PulverizerInfo() {
		x1 = BigInteger.ONE;
		y1 = BigInteger.ZERO;
		x2 = BigInteger.ZERO;
		y2 = BigInteger.ONE;
	}

	public void update(BigInteger q) {
		BigInteger tempx = x1.subtract(q.multiply(x2));
		BigInteger tempy = y1.subtract(q.multiply(y2));
		x1 = x2;
		y1 = y2;
		x2 = tempx;
		y2 = tempy;
	}

	public BigInteger getX1() {
		return x1;
	}

	public BigInteger getY1() {
		return y1;
	}

	public BigInteger getX2() {
		return x2;
	}

	public BigInteger getY2() {
		return y2;
	}

}
