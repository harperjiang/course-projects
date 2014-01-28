package colorgen;
import java.text.MessageFormat;

public class ColorGen {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int vertexCount = 4;
		int colorCount = 3;
//		int[][] edges = new int[][] { new int[] { 1, 2 }, new int[] { 1, 3 },
//				new int[] { 2, 3 }, new int[] { 2, 4 }, new int[] { 2, 5 },
//				new int[] { 3, 5 }, new int[] { 3, 6 }, new int[] { 4, 5 },
//				new int[] { 5, 6 } };
		int[][] edges = new int[][] { new int[] { 1, 2 }, new int[] { 1, 3 },
				new int[] { 1, 4 }, new int[] { 2, 3 }, new int[] { 2, 4 },
				new int[] { 3, 4 } };
		for (int i = 0; i < vertexCount; i++)
			for (int j = 0; j < colorCount; j++)
				System.out.println("(define V" + (i + 1) + (j + 1) + "::bool)");

		System.out.println(";; Each vertex must be colored");
		for (int i = 0; i < vertexCount; i++) {
			System.out.println(MessageFormat.format(
					"(assert (=> (not {0}) (or {1} {2})))", "V" + (i + 1) + 1,
					"V" + (i + 1) + 2, "V" + (i + 1) + 3));
		}

		for (int[] edge : edges) {
			System.out.println(MessageFormat.format(";; For Edge {0},{1}",
					edge[0], edge[1]));
			System.out.println(MessageFormat.format(
					"(assert (=> {0} (not {1})))", "V" + edge[0] + 1, "V"
							+ edge[1] + 1));
			System.out.println(MessageFormat.format(
					"(assert (=> {0} (not {1})))", "V" + edge[0] + 2, "V"
							+ edge[1] + 2));
			System.out.println(MessageFormat.format(
					"(assert (=> {0} (not {1})))", "V" + edge[0] + 3, "V"
							+ edge[1] + 3));
		}
		
		System.out.println("(check)");
	}
}
