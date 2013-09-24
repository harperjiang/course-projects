package ass2.crack;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;

public class Analysis {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(
				new FileInputStream("src/ass2/crack/translate")));
		String line = br.readLine();
		br.close();

		int x = 9;
		Set<String> done = new HashSet<String>();

		// Find a common x-character words
		for (int i = 0; i < line.length() - x; i++) {
			String common = line.substring(i, i + x);
			if (done.contains(common))
				continue;
			else
				done.add(common);
			int count = 0;
			for (int j = i; j < line.length() - x; j++) {
				if (common.equals(line.substring(j, j + x))) {
					count++;
				}
			}
			if (count > 2) {
				System.out.println(common);
				System.out.println(count);
			}
		}

//		// Find two consecutive characters
//		HashMap<String,>
//		for (int i = 0; i < line.length() - 2; i++) {
//			if (line.charAt(i) == line.charAt(i + 1)) {
//				String con = line.substring(i,i+2);
//			}
//		}
	}

}
