package ass1.crack;

import utils.Dictionary;

public class CaesarDictionary implements Dictionary {

	private int index;

	public CaesarDictionary(int index) {
		this.index = index;
	}

	public char lookup(char input) {
		if (Character.isUpperCase(input)) {
			int result = input + index;
			while (result > 'Z')
				result -= 26;
			return (char) result;
		}
		if (Character.isLowerCase(input)) {
			int result = input + index;
			while (result > 'z')
				result -= 26;
			return (char) result;
		}
		throw new IllegalArgumentException("Input " + input
				+ " is not a character");
	}

}
