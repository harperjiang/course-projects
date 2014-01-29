package checkboard;

import checkboard.model.MutilatedModel;
import common.model.StatementPrinter;

public class Checkboard {

	public static void main(String[] args) {

		MutilatedModel normal = new MutilatedModel(4, 4);
		StatementPrinter.print(normal.generate(), System.out);
	}
}
