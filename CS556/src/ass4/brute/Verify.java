package ass4.brute;

import java.math.BigInteger;
import java.text.MessageFormat;

import tools.ec.EllipticCurve;
import tools.ec.EllipticCurve.Element;

public class Verify {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		EllipticCurve curve = new EllipticCurve(new BigInteger(
				"231980187997634794246138521723892165531"), new BigInteger(
				"286458106491124997002528249079664631375"), new BigInteger(
				"300957219209219074658154646971415184777"));
		Element g = new Element(curve, new BigInteger(
				"147686244687917713362777524310538490730"), new BigInteger(
				"83517868646140609087900046649718421315"));
//		Element target = new Element(curve, new BigInteger(
//				"216591050567009152291214325597583347779"), new BigInteger(
//				"107398660888944827631602166762428987345"));
		Element target = new Element(curve, new BigInteger(
				"126619164277821060853358933323435416364"), new BigInteger(
				"158108872031274340029916308842712637005"));
		int threadCount = 6;
		Element inc = g.mul(threadCount);
		for (int i = 0; i < threadCount; i++) {
			CalculateThread thread = new CalculateThread(i, g.mul(i + 1), inc,
					target);
			thread.start();
		}
	}

	public static final class CalculateThread extends Thread {
		private int number;
		private Element start;
		private Element inc;
		private Element target;

		public CalculateThread(int number, Element start, Element inc,
				Element target) {
			super();
			this.number = number;
			this.start = start;
			this.inc = inc;
			this.target = target;
		}

		public void run() {
			Element current = start;
			int counter = 1;
			while (!current.equals(target)) {
				current = current.add(inc);
				counter += 1;
//				if (counter % 10 == 0) {
//					System.out.println(MessageFormat.format(
//							"Processed:{0}:{1}, value {2}", number, counter,
//							current));
//				}
			}
			System.out.println(MessageFormat.format("Success:{0}:{1}", number,
					counter));
			System.exit(0);
		}
	}
}
