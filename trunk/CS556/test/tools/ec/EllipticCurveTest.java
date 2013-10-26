package tools.ec;

import static org.junit.Assert.assertEquals;

import java.math.BigInteger;

import org.junit.Test;

public class EllipticCurveTest {

	@Test
	public void testCalculate() {
		EllipticCurve ec = new EllipticCurve(new BigInteger("43"),
				new BigInteger("4"), new BigInteger("34"));
		assertEquals(new BigInteger("41").pow(2).mod(new BigInteger("43")),
				ec.calculate(new BigInteger("12")));
	}

}
