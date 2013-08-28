package ass1;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class Assignment1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(
				new FileInputStream("src/ass1/input")));
		StringBuilder sb = new StringBuilder();
		String line = null;
		while ((line = br.readLine()) != null) {
			sb.append(line);
			sb.append('\n');
		}
		br.close();
		//
		// Map<Character, Integer> counter = new HashMap<Character, Integer>();
		// for (int i = 0; i < sb.length(); i++) {
		// if (counter.containsKey(sb.charAt(i))) {
		// counter.put(sb.charAt(i), counter.get(sb.charAt(i)) + 1);
		// } else {
		// counter.put(sb.charAt(i), 1);
		// }
		// }
		// for (Entry<Character, Integer> entry : counter.entrySet()) {
		// System.out.println(MessageFormat.format("{0}\t{1}", entry.getKey(),
		// entry.getValue()));
		// }

		// Dictionary dict = new OneOneDictionary(new char[][] { { 'S', 'E' },
		// { 'U', 'T' }, { 'O', 'A' }, { 'Y', 'O' }, { 'W', 'I' },
		// { 'H', 'N' }, { 'R', 'S' }, { 'X', 'H' }, { 'L', 'H' },
		// { 'B', 'D' }, { 'Z', 'L' }, { 'D', 'C' }, { 'T', 'U' },
		// { 'A', 'M' }, { 'Q', 'W' }, { 'P', 'F' }, { 'E', 'G' },
		// { 'J', 'Y' }, { 'V', 'P' }, { 'G', 'B' }, { 'M', 'V' },
		// { 'K', 'K' }, { 'I', 'J' } });
		Dictionary dict = new OneOneDictionary(new char[][] {{ 'U', 't' },
				{ 'L', 'h' }, { 'O', 'i' }, { 'Y', 's' }, { 'S', 'e' },
				{ 'X', 'a' }, { 'V', 'g' }, { 'H', 'n' }, { 'Q', 'm' },{ 'M', 'x' },{ 'W', 'o' },
				{ 'P', 'f' },
				{ 'A', 'p' }, { 'E', 'l' } , { 'B', 'c' }, { 'R', 'r' }, { 'T', 'y' },
				{ 'D', 'd' }, { 'Z', 'u' }, { 'K', 'v' }, { 'J', 'b' },
				{ 'I', 'k' }, { 'G', 'w' }});
		PrintWriter pw = new PrintWriter(new FileOutputStream("output"));
		for (int l = 0; l < sb.length(); l++) {
			pw.write(dict.lookup(sb.charAt(l)));
		}
		pw.close();

	}

}
