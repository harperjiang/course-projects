package sudoku.model;

import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.List;

import common.model.Assert;
import common.model.Check;
import common.model.Constant;
import common.model.Declare;
import common.model.Model;
import common.model.Operator;
import common.model.Predicate;
import common.model.Statement;
import common.model.Type;
import common.model.Variable;

public class SudokuModel implements Model {

	private int size;

	private List<int[]> assigned;

	public SudokuModel(int size) {
		super();
		this.size = size;
		reset();
	}

	public void setNumber(int i, int j, int value) {
		if (value > size * size || value <= 0) {
			throw new IllegalArgumentException(MessageFormat.format(
					"Value {0} is not in valid range", value));
		}
		assigned.add(new int[] { i, j, value });
	}

	public void reset() {
		assigned = new ArrayList<int[]>();
	}

	@Override
	public List<Statement> generate() {
		int total = size * size * size * size;
		List<Statement> result = new ArrayList<Statement>();

		String varPattern = "var_{0}";
		// Generate variables
		for (int i = 0; i < total; i++) {
			result.add(new Declare(MessageFormat.format(varPattern, i),
					Type.Int));
		}
		// Range Check
		for (int i = 0; i < total; i++) {
			String var = MessageFormat.format(varPattern, i);
			result.add(new Assert(new Predicate(Operator.AND, new Predicate(
					Operator.GE, new Variable(var), new Constant(1)),
					new Predicate(Operator.LE, new Variable(var), new Constant(
							size * size)))));
		}
		// Assigned values
		for (int[] assign : assigned) {
			String var = MessageFormat.format(varPattern,
					translate(assign[0], assign[1]));
			result.add(new Assert(new Predicate(Operator.EQUAL, new Variable(
					var), new Constant(assign[2]))));
		}
		// Limitations
		// Columns and rows
		for (int i = 0; i < size * size; i++) {
			for (int j = 0; j < size * size; j++) {
				for (int k = j + 1; k < size * size; k++) {
					result.add(new Assert(new Predicate(Operator.NOT,
							new Predicate(Operator.EQUAL, new Variable(
									MessageFormat.format(varPattern,
											translate(i, j))), new Variable(
									MessageFormat.format(varPattern,
											translate(i, k)))))));
					result.add(new Assert(new Predicate(Operator.NOT,
							new Predicate(Operator.EQUAL, new Variable(
									MessageFormat.format(varPattern,
											translate(j, i))), new Variable(
									MessageFormat.format(varPattern,
											translate(k, i)))))));
					result.add(new Assert(new Predicate(Operator.NOT,
							new Predicate(Operator.EQUAL, new Variable(
									MessageFormat.format(varPattern,
											sqrtranslate(i, j))), new Variable(
									MessageFormat.format(varPattern,
											sqrtranslate(i, k)))))));
				}
			}
		}

		result.add(new Check());
		return result;
	}

	private int translate(int i, int j) {
		return i * getWidth() + j;
	}

	private int sqrtranslate(int i, int j) {
		// The j items of the i block
		return translate((i / size) * size + (j / size), (i % size) * size
				+ (j % size));
	}

	public int getWidth() {
		return size * size;
	}

	public void setSize(int value) {
		this.size = value;
		reset();
	}
}
