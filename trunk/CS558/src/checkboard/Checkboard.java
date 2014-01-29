package checkboard;

import checkboard.model.MutilatedModel;

import common.model.Model;
import common.model.StatementPrinter;

public class Checkboard {

	public static void main(String[] args) {

		Model model = new MutilatedModel(4, 4);
		StatementPrinter.print(model.generate(), System.out);
	}
}
