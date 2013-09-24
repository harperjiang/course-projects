package tools.gcd;

public class PulverizerInfo {

	private long x1;

	private long y1;

	private long x2;

	private long y2;

	public PulverizerInfo() {
		x1 = 1;
		y1 = 0;
		x2 = 0;
		y2 = 1;
	}

	public void update(long q) {
		long tempx = x1 - q * x2;
		long tempy = y1 - q * y2;
		x1 = x2;
		y1 = y2;
		x2 = tempx;
		y2 = tempy;
	}

	public long getX1() {
		return x1;
	}

	public long getY1() {
		return y1;
	}

	public long getX2() {
		return x2;
	}

	public long getY2() {
		return y2;
	}

}
