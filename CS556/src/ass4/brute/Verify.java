package ass4.brute;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.text.NumberFormat;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import tools.ec.EllipticCurve;
import tools.ec.EllipticCurve.Element;

public class Verify {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {

		Pattern ptn = Pattern
				.compile("Processed:(\\d+):([\\d,]+[\\d]+), value \\((\\d+),(\\d+)\\)");

		EllipticCurve curve = new EllipticCurve(new BigInteger(
				"231980187997634794246138521723892165531"), new BigInteger(
				"286458106491124997002528249079664631375"), new BigInteger(
				"300957219209219074658154646971415184777"));
		Element g = new Element(curve, new BigInteger(
				"147686244687917713362777524310538490730"), new BigInteger(
				"83517868646140609087900046649718421315"));

		BufferedReader br = new BufferedReader(new InputStreamReader(
				new FileInputStream("src/ass4/brute/history")));
		String line = null;
		while ((line = br.readLine()) != null) {
			Matcher matcher = ptn.matcher(line);
			if (matcher.matches()) {
				int x = Integer.valueOf(matcher.group(1));
				Long y = NumberFormat.getNumberInstance(java.util.Locale.US)
						.parse(matcher.group(2)).longValue();
				Element element = new Element(curve, new BigInteger(
						matcher.group(3)), new BigInteger(matcher.group(4)));
				if (!element.equals(g.mul((y - 1) * 6 + x + 1))) {
					System.out.println(line);
				}
			} else {
				throw new IllegalArgumentException("Not recognized:" + line);
			}
		}

		br.close();
	}

}
