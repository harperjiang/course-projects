package colorgen;

import java.text.MessageFormat;

public class ColorZ3Generator {

	public static void main(String[] args) {
		int verticeNum = 4;

		// int[][] edges = new int[][] { new int[] { 1, 2 }, new int[] { 1, 3 },
		// new int[] { 2, 3 }, new int[] { 2, 4 }, new int[] { 2, 5 },
		// new int[] { 3, 5 }, new int[] { 3, 6 }, new int[] { 4, 5 },
		// new int[] { 5, 6 } };

		int[][] edges = new int[][] { new int[] { 1, 2 }, new int[] { 1, 3 },
				new int[] { 1, 4 }, new int[] { 2, 3 }, new int[] { 2, 4 },
				new int[] { 3, 4 } };

		int colorCount = 3;

		for (int i = 0; i < verticeNum; i++) {
			for (int j = 0; j < colorCount; j++)
				System.out.println(MessageFormat.format(
						"(declare-const c{0}{1} Bool)", i + 1, j + 1));
		}

		for (int i = 0; i < verticeNum; i++) {
			System.out
					.println(MessageFormat
							.format("(assert (and (xor c{0}1 c{0}2 c{0}3) (not (or (and (not c{0}1) c{0}2 c{0}3) (and c{0}1 (or c{0}2 c{0}3))))))",
									i + 1));
		}

		for (int[] edge : edges) {
			System.out
					.println(MessageFormat
							.format("(assert (and (not (and c{0}1 c{1}1)) (not (and c{0}2 c{1}2)) (not (and c{0}3 c{1}3))))",
									edge[0], edge[1]));
		}
		System.out.println("(check-sat)");
		System.out.println("(get-model)");
	}
}
