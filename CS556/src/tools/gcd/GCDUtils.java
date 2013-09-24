package tools.gcd;

import java.math.BigInteger;

public class GCDUtils {

	public static PulverizerInfo gcd(BigInteger a, BigInteger b) {
		if (a == null || b == null || a.compareTo(b) <= 0) {
			throw new IllegalArgumentException();
		}
		PulverizerInfo pi = new PulverizerInfo();
		BigInteger ap = a, bp = b;
		while (!bp.equals(BigInteger.ONE) && !bp.equals(BigInteger.ZERO)) {
			pi.update(ap.divide(bp));
			BigInteger temp = ap.mod(bp);
			ap = bp;
			bp = temp;
		}
		if (bp.equals(BigInteger.ONE))
			return pi;
		else
			return null;
	}

	public static BigInteger inverse(BigInteger p, BigInteger n) {
		PulverizerInfo pi = gcd(n, p);
		if (pi == null)
			return null;
		return pi.getY2();
	}

	public static void main(String[] args) {
		PulverizerInfo pi = gcd(new BigInteger("757"), new BigInteger("353"));
		if (pi != null) {
			System.out.println(pi.getX2());
			System.out.println(pi.getY2());
		}
	}
}
