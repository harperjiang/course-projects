package ass2.project;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {

		if (args.length == 0)
			return;
		if ("-h".equals(args[0])) {
			System.out.println("Charwise RSA Encryption:");
			System.out
					.println("\t-genkey <bitlength> <public_key_file> <private_key_file>: Generate Public/Private Keypairs and write to files");
			System.out
					.println("\t-encrypt <public_key_file> <plain_text> <cipher_text>: Encrypt Plain text");
			System.out
					.println("\t-encrypt <private_key_file> <cipher_text> <plain_text>: Decrypt Cipher text");
		}
		if ("-genkey".equals(args[0])) {
			int bitlength = Integer.parseInt(args[1]);
			PrintWriter publicFile = new PrintWriter(new FileOutputStream(
					args[2]));
			PrintWriter privateFile = new PrintWriter(new FileOutputStream(
					args[3]));
			KeyGenerator kgen = new KeyGenerator(bitlength);
			publicFile.println(kgen.getBase());
			publicFile.println(kgen.getPublicKey());
			privateFile.println(kgen.getBase());
			privateFile.println(kgen.getPrivateKey());
			publicFile.close();
			privateFile.close();
		}
		if ("-encrypt".equals(args[0])) {
			BufferedReader keyreader = new BufferedReader(
					new InputStreamReader(new FileInputStream(args[1])));
			FileInputStream input = new FileInputStream(args[2]);
			FileOutputStream output = new FileOutputStream(args[3]);

			BigInteger base = new BigInteger(keyreader.readLine());
			BigInteger key = new BigInteger(keyreader.readLine());
			CharwiseRSA cwrsa = new CharwiseRSA(base, key, null);
			cwrsa.encrypt(input, output);
			input.close();
			output.close();
			keyreader.close();
		}
		if ("-decrypt".equals(args[0])) {
			BufferedReader keyreader = new BufferedReader(
					new InputStreamReader(new FileInputStream(args[1])));
			FileInputStream input = new FileInputStream(args[2]);
			FileOutputStream output = new FileOutputStream(args[3]);

			BigInteger base = new BigInteger(keyreader.readLine());
			BigInteger key = new BigInteger(keyreader.readLine());
			CharwiseRSA cwrsa = new CharwiseRSA(base, null, key);
			cwrsa.decrypt(input, output);
			input.close();
			output.close();
			keyreader.close();
		}
	}

}
