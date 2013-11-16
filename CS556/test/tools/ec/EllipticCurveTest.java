package tools.ec;

import static org.junit.Assert.*;
import static org.junit.Assert.assertEquals;

import java.math.BigInteger;

import org.junit.Test;

import tools.ec.EllipticCurve.Element;

public class EllipticCurveTest {

	@Test
	public void testCalculate() {
		EllipticCurve ec = new EllipticCurve(new BigInteger("43"),
				new BigInteger("4"), new BigInteger("34"));
		assertEquals(new BigInteger("41").pow(2).mod(new BigInteger("43")),
				ec.calculate(new BigInteger("12")));
	}

	@Test
	public void testElementEquals() {
		EllipticCurve ec = new EllipticCurve(new BigInteger("43"),
				new BigInteger("4"), new BigInteger("34"));
		Element element1 = new Element(ec, new BigInteger("12"),
				new BigInteger("41"));
		Element element2 = new Element(ec, new BigInteger("12"),
				new BigInteger("41"));
		Element element3 = EllipticCurve.ZERO;
		Element element4 = EllipticCurve.ZERO;

		assertEquals(element1, element2);
		assertTrue(!element2.equals(element3));
		assertEquals(element3, element4);
	}

}
