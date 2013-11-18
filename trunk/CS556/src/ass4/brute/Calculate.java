package ass4.brute;

import java.math.BigInteger;

import tools.ec.EllipticCurve;
import tools.ec.EllipticCurve.Element;

public class Calculate {

	public static void main(String[] args) {
		EllipticCurve curve = new EllipticCurve(new BigInteger(
				"231980187997634794246138521723892165531"), new BigInteger(
				"286458106491124997002528249079664631375"), new BigInteger(
				"300957219209219074658154646971415184777"));
		Element g = new Element(curve, new BigInteger(
				"147686244687917713362777524310538490730"), new BigInteger(
				"83517868646140609087900046649718421315"));

		Element a2 = g.mul((2120000000l - 1) * 6l + (3 + 1));
		System.out.println(a2);
	}
}
