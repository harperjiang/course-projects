package tools.gcd;

public class GCDUtils {

	public static PulverizerInfo gcd(long a, long b) {
		PulverizerInfo pi = new PulverizerInfo();
		long ap = a, bp = b;
		while (bp != 1 && bp != 0) {
			pi.update(ap / bp);
			long temp = ap % bp;
			ap = bp;
			bp = temp;
		}
		if (bp == 1)
			return pi;
		else
			return null;
	}

	public static void main(String[] args) {
		PulverizerInfo pi = gcd(757, 353);
		if (pi != null) {
			System.out.println(pi.getX2());
			System.out.println(pi.getY2());
		}
	}
}
