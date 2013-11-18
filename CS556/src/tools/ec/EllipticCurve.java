package tools.ec;

import java.math.BigInteger;
import java.text.MessageFormat;

public class EllipticCurve {

	// y^2 = x^3 + ax + b

	public static Element ZERO = new Element(null, BigInteger.ZERO,
			BigInteger.ZERO);

	private BigInteger p;
	private BigInteger a;
	private BigInteger b;

	public EllipticCurve(BigInteger p, BigInteger a, BigInteger b) {
		this.p = p;
		this.a = a;
		this.b = b;
	}

	protected BigInteger calculate(BigInteger x) {
		return x.pow(3).add(a.multiply(x)).add(b).mod(p);
	}

	protected void validate(BigInteger x, BigInteger y) {
		if (!y.pow(2).mod(p).equals(calculate(x))) {
			throw new IllegalArgumentException();
		}
	}

	public static class Element {

		EllipticCurve curve;
		BigInteger x;
		BigInteger y;

		public Element(EllipticCurve curve, BigInteger x, BigInteger y) {
			if (!(x.equals(BigInteger.ZERO) && y.equals(BigInteger.ZERO))) {
				this.curve = curve;
				this.x = x.mod(curve.p);
				this.y = y.mod(curve.p);
				curve.validate(x, y);
			}
		}

		public BigInteger getX() {
			return x;
		}

		public BigInteger getY() {
			return y;
		}

		public boolean equals(Object another) {
			if (another instanceof Element) {
				if (this == ZERO || another == ZERO) {
					return this == another;
				}
				Element ae = (Element) another;
				return ae.curve.equals(curve) && ae.x.equals(x)
						&& ae.y.equals(y);
			}
			return super.equals(another);
		}

		public Element negate() {
			return new Element(this.curve, x, y.negate());
		}

		@Override
		public String toString() {
			return MessageFormat.format("({0},{1})", this.x.toString(),
					this.y.toString());
		}

		public Element add(Element another) {
			if (another.equals(ZERO))
				return this;
			if (this.equals(ZERO))
				return another;

			if (this.curve != another.curve)
				return null;

			if (this.x.equals(another.x) && this.y.equals(another.y)) {
				// m = (3x1^2+a)(2y1)^-1
				BigInteger m = new BigInteger("3")
						.multiply(this.x.pow(2))
						.add(curve.a)
						.multiply(
								this.y.multiply(new BigInteger("2"))
										.modInverse(curve.p)).mod(curve.p);
				// x3 = m^2 - 2x1
				// y3 = y1 + m(x3-x1)
				BigInteger x3 = m.pow(2)
						.subtract(new BigInteger("2").multiply(this.x))
						.mod(curve.p);
				BigInteger y3 = this.y.add(m.multiply(x3.subtract(this.x)))
						.mod(curve.p);
				return new Element(this.curve, x3, y3.negate());
			} else if (this.x.equals(another.x) && !this.y.equals(another.y)) {
				return EllipticCurve.ZERO;
			} else {
				// m = (y2-y1)(x2-x1)^(-1)
				BigInteger m = another.y
						.subtract(this.y)
						.multiply(
								another.x.subtract(this.x).modInverse(curve.p))
						.mod(curve.p);
				// x3 = m^2 - (x1+x2)
				BigInteger x3 = m.pow(2).subtract(this.x.add(another.x))
						.mod(curve.p);
				// y3 = y2 + m (x3-x2)
				BigInteger y3 = another.y.add(
						m.multiply(x3.subtract(another.x))).mod(curve.p);
				return new Element(curve, x3, y3.negate());
			}
		}

		public Element slowmul(int num) {
			Element now = this;
			for (int i = 1; i < num; i++) {
				now = now.add(this);
			}
			return now;
		}

		public Element mul(long num) {
			Element now = this;
			int count = 0;
			while (Math.pow(2, count) <= num) {
				count++;
			}
			Element[] pows = new Element[count];
			pows[0] = now;
			for (int i = 1; i < pows.length; i++) {
				pows[i] = pows[i - 1].add(pows[i - 1]);
			}
			Element result = EllipticCurve.ZERO;
			for (int i = 0; i < count; i++) {
				if ((num & (1l << i)) != 0) {
					result = result.add(pows[i]);
				}
			}
			return result;
		}

		public Element mul(BigInteger num) {
			Element now = this;
			int count = 0;
			BigInteger two = new BigInteger("2");
			while (two.pow(count).compareTo(num) <= 0) {
				count++;
			}
			Element[] pows = new Element[count];
			pows[0] = now;
			for (int i = 1; i < pows.length; i++) {
				pows[i] = pows[i - 1].add(pows[i - 1]);
			}
			Element result = EllipticCurve.ZERO;
			for (int i = 0; i < count; i++) {
				if (!(num.and(BigInteger.ONE.shiftLeft(i)))
						.equals(BigInteger.ZERO)) {
					result = result.add(pows[i]);
				}
			}
			return result;
		}
	}

	public static void main(String[] args) {
		EllipticCurve ec = new EllipticCurve(new BigInteger("7"),
				new BigInteger("1"), new BigInteger("1"));
		Element g = new Element(ec, new BigInteger("0"), new BigInteger("1"));
		// Element e = new Element(ec, new BigInteger("6"), new
		// BigInteger("39"));
		// Element e2 = new Element(ec, new BigInteger("12"), new
		// BigInteger("41"));
		// Element now = e.mul(2);
		// System.out.println(MessageFormat.format("({0},{1})", now.x, now.y));
		for (int i = 1; i < 20; i++) {
			Element now = g.mul(i);
			System.out.println(MessageFormat.format("({0},{1})", now.x, now.y));
		}
	}
}
