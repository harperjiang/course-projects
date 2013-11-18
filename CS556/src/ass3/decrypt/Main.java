package ass3.decrypt;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {

	public static void main(String[] args) throws Exception {
		BigInteger p = new BigInteger(
				"211287523889848166456771978073530465593093161450010064509303400255860514422619");
		BigInteger g = new BigInteger(
				"15944282073914562075116370489962003433567850159612874030242082495627173757989");
		BigInteger b = new BigInteger(
				"99875420304905788162304238315680480125682219886353666515441718590579015480458");
		BigInteger a = new BigInteger(
				"102112374625719848836417645466897582644268266380360636462856219195606277562091");

		BufferedReader br = new BufferedReader(new InputStreamReader(
				new FileInputStream("src/ass3/decrypt/cipher")));
		PrintWriter pw = new PrintWriter(new FileOutputStream(
				"src/ass3/decrypt/plain"));

		String line = null;
		while ((line = br.readLine()) != null) {
			String[] parts = line.split(",");
			BigInteger sand = new BigInteger(parts[0]);
			BigInteger cipher = new BigInteger(parts[1]);
			pw.print((char) cipher.multiply(sand.modPow(a, p).modInverse(p))
					.mod(p).intValue());
		}

		br.close();
		pw.close();
	}

}
