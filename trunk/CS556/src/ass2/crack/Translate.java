package ass2.crack;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;

public class Translate {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(
				new FileInputStream("src/ass2/input")));
		PrintWriter pw = new PrintWriter(new FileOutputStream("translate"));
		String line = null;

		Map<BigInteger, Character> translate = new HashMap<BigInteger, Character>();

		Map<Character, Integer> counter = new HashMap<Character, Integer>();

		while ((line = br.readLine()) != null) {
			BigInteger number = new BigInteger(line);
			if (!translate.containsKey(number)) {
				translate.put(number, (char) ('A' + translate.size()));
			}
			Character cha = translate.get(number);
			if (!counter.containsKey(cha)) {
				counter.put(cha, 0);
			}
			counter.put(cha, counter.get(cha) + 1);
			pw.print(cha);
		}
		System.out.println(translate.size());
		br.close();
		pw.close();
		counter.size();
	}

}
