package ass1.project;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class CipherTest {

	@Test
	public void testEncrypt() {
		byte[] input = "ABC".getBytes();
		byte[] result = new Cipher().encrypt(input);
		assertEquals("FAKFAYXZXZXZ", new String(result));
	}

	@Test
	public void testDecrypt() {
		byte[] input = "FAKFAYXZXZXZ".getBytes();
		assertEquals("ABC", new String(new Cipher().decrypt(input)));
	}

}
