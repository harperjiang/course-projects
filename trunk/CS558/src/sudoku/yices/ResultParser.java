package sudoku.yices;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ResultParser {

	private Map<String, String> values;

	public Map<String, String> getValues() {
		return values;
	}

	static Pattern pattern = Pattern.compile("\\(= a(\\d+) (\\d+)\\)");

	public void parse(InputStream inputStream) throws IOException {
		values = new HashMap<String, String>();
		BufferedReader br = new BufferedReader(new InputStreamReader(
				inputStream));
		String line = null;
		while ((line = br.readLine()) != null) {
			if ("unsat".equals(line)) {
				values = null;
				return;
			}
			Matcher matcher = pattern.matcher(line);
			if (matcher.matches()) {
				values.put("a" + matcher.group(1), matcher.group(2));
			}
		}
	}

}