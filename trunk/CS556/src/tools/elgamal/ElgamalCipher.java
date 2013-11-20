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

	private Key key;

	private ByteArrayOutputStream buffer;

	public ElgamalCipher() {
	}

	public void init(int type, Object key) {
		this.type = type;
		if (!(key instanceof Key)) {
			throw new IllegalArgumentException();
		}
		this.key = (Key) key;
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
				PublicKey pk = (PublicKey) key;
				BigInteger mask = pk.getG().modPow(k, pk.getP());
				BigInteger sand = pk.getB().modPow(k, pk.getP());
				BigInteger msg = m.multiply(sand).mod(pk.getP());
				// TODO Write msg and sand
			}
		}
		case DECRYPT_MODE: {
			BigInteger msg = null;
			BigInteger sand = null;
			PrivateKey pk = (PrivateKey) key;
			BigInteger mask = sand.modPow(pk.getA(), pk.getP());
			BigInteger m = msg.multiply(mask.modInverse(pk.getP())).mod(
					pk.getP());
			// TODO Write m
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
