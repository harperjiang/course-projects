package tools.elgamal;

import static org.junit.Assert.assertEquals;

import java.math.BigInteger;

import org.junit.Test;

public class ElgamalCipherTest {

	@Test
	public void testDoFinal() {
		KeyGenerator kgen = new KeyGenerator(128);
		PrivateKey prk = kgen.getPrivateKey();
		PublicKey puk = kgen.getPublicKey();

		assertEquals(prk.getG().modPow(prk.getA(), prk.getP()), puk.getB());

		BigInteger m = new BigInteger("84");
		BigInteger k = new BigInteger("123124221341");
		BigInteger sand = puk.getB().modPow(k, puk.getP());
		BigInteger mask = puk.getG().modPow(k, puk.getP());
		BigInteger msg = sand.multiply(m).mod(puk.getP());

		BigInteger sand2 = mask.modPow(prk.getA(), prk.getP());
		assertEquals(sand, sand2);
		BigInteger m2 = sand2.modInverse(prk.getP()).multiply(msg)
				.mod(prk.getP());
		assertEquals(m, m2);

		ElgamalCipher cipher = new ElgamalCipher();
		cipher.init(Cipher.ENCRYPT_MODE, puk);
		cipher.update("This is a text".getBytes());
		byte[] encrypted = cipher.doFinal();

		cipher.init(Cipher.DECRYPT_MODE, prk);
		cipher.update(encrypted);
		byte[] decrypted = cipher.doFinal();
		assertEquals("This is a text", new String(decrypted));
	}

}
