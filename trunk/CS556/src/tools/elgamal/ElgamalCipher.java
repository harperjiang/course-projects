package tools.elgamal;

import java.io.ByteArrayOutputStream;
import java.math.BigInteger;
import java.text.MessageFormat;
import java.util.Random;

/**
 * This is a bitwise-elgamal encryption/decryption
 * 
 * @author Harper
 * 
 */
public class ElgamalCipher implements Cipher {

	private int type;

	private BigInteger key;

	private ByteArrayOutputStream buffer;

	public ElgamalCipher() {
	}

	public void init(int type, Object key) {
		this.type = type;
		if (!(key instanceof BigInteger)) {
			throw new IllegalArgumentException();
		}
		this.key = (BigInteger) key;
		buffer = new ByteArrayOutputStream();
		random = new Random(System.currentTimeMillis());
	}

	public int getType() {
		return type;
	}

	public Object getKey() {
		return key;
	}

	@Override
	public void update(byte[] data) {
		switch (type) {
		case ENCRYPT_MODE: {
			for (byte b : data) {
				BigInteger k = randomSand();
				BigInteger m = BigInteger.valueOf(b);
				
			}
		}
		case DECRYPT_MODE: {
			BigInteger m = 
		}
		default:
			throw new IllegalArgumentException();
		}
	}

	@Override
	public byte[] doFinal() {
		return buffer.toByteArray();
	}

	private Random random;

	private BigInteger randomSand() {
		long a = random.nextLong();
		long b = random.nextLong();
		return new BigInteger(MessageFormat.format("{0}{1}", a, b));
	}
}
