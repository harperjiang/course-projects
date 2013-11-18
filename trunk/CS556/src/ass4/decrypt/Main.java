package ass4.decrypt;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;

import tools.ec.EllipticCurve;
import tools.ec.EllipticCurve.Element;

public class Main {

	public static void main(String[] args) throws Exception {
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
		BigInteger k = new BigInteger("182755680224874988969105090392374859247");

		BufferedReader br = new BufferedReader(new InputStreamReader(
				new FileInputStream("src/ass4/decrypt/cipher")));
		PrintWriter pw = new PrintWriter(new FileOutputStream(
				"src/ass4/decrypt/plain"));
		String line = null;
		while ((line = br.readLine()) != null) {
			String[] parts = line.split(" ");
			try {
				Element cipher = new Element(curve, new BigInteger(parts[0]),
						new BigInteger(parts[1]));
				Element sand = new Element(curve, new BigInteger(parts[2]),
						new BigInteger(parts[3]));
				Element result = cipher.add(sand.mul(k).negate());
				pw.print((char) result.getX().intValue());
			} catch (IllegalArgumentException e) {
				System.out.println(line);
			}
		}
		pw.close();
		br.close();

	}
}
