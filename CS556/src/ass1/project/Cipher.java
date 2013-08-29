package ass1.project;

import java.io.ByteArrayOutputStream;

public class Cipher {

	public byte[] encrypt(byte[] input) {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();

		int remaining = 0;
		int storing = 0;
		for (byte b : input) {
			storing += 8;
			remaining <<= 8;
			remaining += b;

			while (storing >= 9) {
				int extract = remaining >> 9;
				remaining = remaining - (extract << 9);
				storing -= 9;
				bos.write('A' + remaining / 26);
				bos.write('A' + remaining % 26);
			}
		}

		remaining <<= (8 - storing);
		bos.write('A' + remaining / 26);
		bos.write('A' + remaining % 26);
		for (int i = storing; i < 8; i++) {
			bos.write('X');
			bos.write('Z');
		}

		return bos.toByteArray();
	}

	public byte[] decrypt(byte[] input) {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();

		int padding = 0;
		for (int i = input.length - 1; i > 0; i -= 2) {
			if (!(input[i - 1] == 'X' && input[i] == 'Z'))
				break;
			padding++;
		}
		int stored = 0;
		int remaining = 0;
		for (int i = 0; i < input.length - 1 - padding * 2; i += 2) {
			byte first = input[i];
			byte second = input[i + 1];
			remaining = (remaining << 9) + (first - 'A') * 26 + (second - 'A');
			stored += 9;
			while (stored >= 8) {
				int write = remaining >> (stored - 8);
				bos.write(write);
				remaining -= (write << (stored - 8));
				stored -= 8;
			}
		}
		if (!(stored == padding))
			throw new IllegalArgumentException();

		return bos.toByteArray();
	}
}
