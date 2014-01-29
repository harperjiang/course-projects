package checkboard.model;

import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import common.model.Assert;
import common.model.Check;
import common.model.Declare;
import common.model.Model;
import common.model.PredicateHelper;
import common.model.Statement;
import common.model.Type;

public class NormalModel implements Model {

	private int width;

	private int height;

	public NormalModel(int width, int height) {
		this.width = width;
		this.height = height;
	}

	@Override
	public List<Statement> generate() {
		Set<String> definedVars = new HashSet<String>();

		List<Statement> statements = new ArrayList<Statement>();
		// First define variables
		// For each tiles there are at most 4 tiles and at least 2 tiles
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (i > 0) {
					String label = label(number(i, j), number(i - 1, j));
					if (!definedVars.contains(label)) {
						statements.add(new Declare(label, Type.Bool));
						definedVars.add(label);
					}
				}
				if (j > 0) {
					String label = label(number(i, j), number(i, j - 1));
					if (!definedVars.contains(label)) {
						statements.add(new Declare(label, Type.Bool));
						definedVars.add(label);
					}
				}
				if (i < width - 1) {
					String label = label(number(i, j), number(i + 1, j));
					if (!definedVars.contains(label)) {
						statements.add(new Declare(label, Type.Bool));
						definedVars.add(label);
					}
				}
				if (j < height - 1) {
					String label = label(number(i, j), number(i, j + 1));
					if (!definedVars.contains(label)) {
						statements.add(new Declare(label, Type.Bool));
						definedVars.add(label);
					}
				}
			}
		}
		// For each tile, there should be exactly one cover
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				List<String> vars = new ArrayList<String>();
				if (i > 0) {
					vars.add(label(number(i - 1, j), number(i, j)));
				}
				if (j > 0) {
					vars.add(label(number(i, j - 1), number(i, j)));
				}
				if (i < width - 1) {
					vars.add(label(number(i, j), number(i + 1, j)));
				}
				if (j < height - 1) {
					vars.add(label(number(i, j), number(i, j + 1)));
				}
				String[] vs = new String[vars.size()];
				vars.toArray(vs);
				statements.add(new Assert(PredicateHelper.singleOne(vs)));
			}
		}
		statements.add(new Check());
		return statements;
	}

	private String label(int a, int b) {
		int min = Math.min(a, b);
		int max = Math.max(a, b);
		return MessageFormat.format("var_{0}_{1}", min, max);
	}

	private int number(int i, int j) {
		return j * width + i;
	}
}
