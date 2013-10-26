package ass3.brute;

import java.math.BigInteger;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class Cracker {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		BigInteger p = new BigInteger(
				"211287523889848166456771978073530465593093161450010064509303400255860514422619");
		BigInteger g = new BigInteger(
				"15944282073914562075116370489962003433567850159612874030242082495627173757989");
		BigInteger b = new BigInteger(
				"99875420304905788162304238315680480125682219886353666515441718590579015480458");

		long threshold = 100000000000l;
		while (true) {
			System.out.println("Restart...:" + System.currentTimeMillis());
			Random random = new Random(System.currentTimeMillis());

			int counter = 0;
			while (true) {
				if (counter > threshold)
					break;
				long result = random.nextLong();
				// Look for a that g^a mod p = b
				if (g.modPow(BigInteger.valueOf(result), p).equals(b)) {
					System.out.println(result);
					return;
				}
				counter++;
			}

		}
	}

}
