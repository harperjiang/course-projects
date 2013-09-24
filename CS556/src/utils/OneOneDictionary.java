package utils;

import java.util.HashMap;
import java.util.Map;


public class OneOneDictionary implements Dictionary {

	private Map<Character, Character> mappings;

	public OneOneDictionary(char[][] m) {
		mappings = new HashMap<Character, Character>();
		for (char[] cp : m) {
			mappings.put(cp[0], cp[1]);
		}
	}

	public char lookup(char input) {
		if (mappings.containsKey(input)) {
			return mappings.get(input);
		}
		return input;
	}

}
