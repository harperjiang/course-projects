package ass4.brute;

import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.text.MessageFormat;

import tools.ec.EllipticCurve;
import tools.ec.EllipticCurve.Element;

public class Main {

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
		Element target = new Element(curve, new BigInteger(
				"216591050567009152291214325597583347779"), new BigInteger(
				"107398660888944827631602166762428987345"));
		int threadCount = 6;
		Element inc = g.mul(threadCount);
		// for (int i = 0; i < threadCount; i++) {
		// CalculateThread thread = new CalculateThread(i, g.mul(i + 1), inc,
		// target);
		// thread.start();
		// }

		CalculateThread thread1 = new CalculateThread(0, new Element(curve,
				new BigInteger("145697449770187874476326978055883996266"),
				new BigInteger("174948184565688853772477350589115314329")),
				inc, target);
		thread1.setCounter(1560000000l);
		thread1.start();

		CalculateThread thread2 = new CalculateThread(1, new Element(curve,
				new BigInteger("86744068349102061789824003879905891645"),
				new BigInteger("84594757080104559577239545794193972610")), inc,
				target);
		thread2.setCounter(1600000000l);
		thread2.start();

		CalculateThread thread3 = new CalculateThread(2, new Element(curve,
				new BigInteger("177642080504131601247250215333792532415"),
				new BigInteger("106485593792002619071653479487123105629")),
				inc, target);
		thread3.setCounter(1650000000l);
		thread3.start();

		CalculateThread thread4 = new CalculateThread(3, new Element(curve,
				new BigInteger("21128894726749957056603814076103466212"),
				new BigInteger("118869102166829012890598188272916671353")),
				inc, target);
		thread4.setCounter(1630000000l);
		thread4.start();

		CalculateThread thread5 = new CalculateThread(4, new Element(curve,
				new BigInteger("144044002239725645798650253295476906320"),
				new BigInteger("12216884291606090643494028344316964534")), inc,
				target);
		thread5.setCounter(1540000000);
		thread5.start();

		CalculateThread thread6 = new CalculateThread(5, new Element(curve,
				new BigInteger("201881605958699569154366474366082739873"),
				new BigInteger("110116407719661230559194278133623891093")),
				inc, target);
		thread6.setCounter(1560000000l);
		thread6.start();
	}

	public static final class CalculateThread extends Thread {
		private int number;
		private Element start;
		private Element inc;
		private Element target;
		private long counter = 1;

		public CalculateThread(int number, Element start, Element inc,
				Element target) {
			super();
			this.number = number;
			this.start = start;
			this.inc = inc;
			this.target = target;
		}

		public long getCounter() {
			return counter;
		}

		public void setCounter(long counter) {
			this.counter = counter;
		}

		public void run() {
			Element current = start;
			try {
				PrintWriter pw = new PrintWriter(new FileOutputStream(
						"history_" + number));
				while (!current.equals(target)) {
					current = current.add(inc);
					counter += 1;
					if (counter % 10000000 == 0) {
						String message = MessageFormat.format(
								"Processed:{0}:{1}, value {2}", number,
								Long.toString(counter), current);
						System.out.println(message);
						pw.println(message);
						pw.flush();
					}
				}
				pw.close();
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
			System.out.println(MessageFormat.format("Success:{0}:{1}", number,
					counter));
			System.exit(0);
		}
	}
}
