package tools.elgamal;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.math.BigInteger;
import java.nio.ByteBuffer;
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

	private ByteArrayOutputStream output;

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
		output = new ByteArrayOutputStream();
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
		try {
			buffer.write(data);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	@Override
	public byte[] doFinal() {
		byte[] data = buffer.toByteArray();
		ByteArrayInputStream input = new ByteArrayInputStream(data);
		switch (type) {
		case ENCRYPT_MODE: {
			int next = -1;
			while ((next = input.read()) != -1) {
				BigInteger k = randomSand();
				BigInteger m = BigInteger.valueOf(next);
				PublicKey pk = (PublicKey) key;
				BigInteger mask = pk.getG().modPow(k, pk.getP());
				BigInteger sand = pk.getB().modPow(k, pk.getP());
				BigInteger msg = m.multiply(sand).mod(pk.getP());
				// Write msg and sand
				writeBigInteger(mask, output);
				writeBigInteger(msg, output);
			}
			break;
		}
		case DECRYPT_MODE: {
			while (input.available() > 0) {
				BigInteger mask = readBigInteger(input);
				BigInteger msg = readBigInteger(input);
				PrivateKey pk = (PrivateKey) key;
				BigInteger sand = mask.modPow(pk.getA(), pk.getP());
				BigInteger m = msg.multiply(sand.modInverse(pk.getP())).mod(
						pk.getP());
				// Write m
				output.write(m.intValue());
			}
			break;
		}
		default:
			throw new IllegalArgumentException();
		}
		return output.toByteArray();
	}

	private BigInteger readBigInteger(ByteArrayInputStream input) {
		try {
			// Read the length of byte
			byte[] lenbytes = new byte[4];
			input.read(lenbytes);
			ByteBuffer lenbuf = ByteBuffer.allocate(4).put(lenbytes);
			lenbuf.rewind();
			int length = lenbuf.getInt();
			byte[] databytes = new byte[length];
			input.read(databytes);
			return new BigInteger(databytes);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	private void writeBigInteger(BigInteger num, OutputStream output) {
		byte[] arrays = num.toByteArray();
		try {
			ByteBuffer bb = ByteBuffer.allocate(4).putInt(arrays.length);
			output.write(bb.array());
			output.write(arrays);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	private Random random;

	private BigInteger randomSand() {
		long a = random.nextLong();
		long b = random.nextLong();
		if (a < 0)
			a = -a;
		if (b < 0)
			b = -b;
		return new BigInteger(MessageFormat.format("{0}{1}", String.valueOf(a),
				String.valueOf(b)));
	}
}
