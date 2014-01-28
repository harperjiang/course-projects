package sudoku.yices;

import java.io.PrintStream;
import java.text.MessageFormat;

public class RuleGenerator {

	private int n;

	private transient PrintStream pw;

	public RuleGenerator(int n) {
		super();
		this.n = n;
	}

	public void generateGlobalRules(PrintStream pw) {
		this.pw = pw;
		generateVariables();
		generateRules();
	}

	public void check() {
		pw.println("(check)");
	}

	protected void generateVariables() {
		int size = n * n;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				pw.println(MessageFormat.format("(define a{0}::int)", i * size
						+ j));
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				pw.println(MessageFormat.format("(assert (<= a{0} {1}))", i
						* size + j, size));
				pw.println(MessageFormat.format("(assert (>= a{0} {1}))", i
						* size + j, 1));
			}
		}
	}

	protected void generateRules() {
		int size = n * n;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				for (int k = j + 1; k < size; k++) {
					pw.println(MessageFormat.format("(assert (/= a{0} a{1}))",
							i * size + j, i * size + k));
					pw.println(MessageFormat.format("(assert (/= a{0} a{1}))",
							j * size + i, k * size + i));
					pw.println(MessageFormat.format("(assert (/= a{0} a{1}))",
							((i / n) * n + j / n) * size + (i % n) * n + j % n,
							((i / n) * n + k / n) * size + (i % n) * n + k % n));
				}
			}
		}
	}

	public void generateGivenRules(int i, int j, int val) {
		int size = n * n;
		if (i >= size || i < 0 || j >= size || j < 0) {
			throw new IllegalArgumentException(MessageFormat.format(
					"({0},{1}) is not a valid coordinator", i, j));
		}
		if (val > size || val < 1)
			throw new IllegalArgumentException(MessageFormat.format(
					"{0} is not a valid value", val));
		pw.println(MessageFormat.format("(assert (= a{0} {1}))", i * size + j,
				val));
	}
}
