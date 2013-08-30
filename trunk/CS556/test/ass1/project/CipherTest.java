package ass1.project;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import ass1.project.core.Ass1Cipher;

public class CipherTest {

	@Test
	public void testEncrypt() {
		byte[] input = "ABC".getBytes();
		byte[] result = new Ass1Cipher().encrypt(input);
		assertEquals("FAKFAYXZXZXZ", new String(result));
	}

	@Test
	public void testDecrypt() {
		byte[] input = "FAKFAYXZXZXZ".getBytes();
		assertEquals("ABC", new String(new Ass1Cipher().decrypt(input)));
	}

}
