package sudoku.model;

import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import sudoku.yices.ResultParser;
import sudoku.yices.RuleGenerator;

public class SudokuSolver {

	private boolean ready = true;

	private int size = 3;

	private int[] values = new int[3 * 3 * 3 * 3];

	public int getSize() {
		return size;
	}

	public void setSize(int size) {
		this.size = size;
		reset();
	}

	public void setNumber(int i, int j, int val) {
		if (!ready)
			throw new IllegalStateException();
		if (val > size * size || val <= 0)
			throw new IllegalArgumentException();
		values[i * size * size + j] = val;
	}

	public void reset() {
		values = new int[size * size * size * size];
		for (int i = 0; i < values.length; i++)
			values[i] = 0;
		ready = true;
	}

	public Map<String, Integer> solve() {
		if (!ready)
			throw new IllegalStateException();
		try {
			Map<String, Integer> result = new HashMap<String, Integer>();

			Process p = Runtime.getRuntime().exec("yices -e");

			RuleGenerator rg = new RuleGenerator(getSize());
			int s = getWidth();
			rg.generateGlobalRules(new PrintStream(p.getOutputStream()));
			for (int i = 0; i < values.length; i++) {
				if (values[i] != 0) {
					rg.generateGivenRules(i / s, i % s, values[i]);
				}
			}
			rg.check();
			p.getOutputStream().write("(exit)\n".getBytes());
			p.getOutputStream().flush();
			Thread.sleep(1000);

			ResultParser parser = new ResultParser();
			parser.parse(p.getInputStream());
			Thread.sleep(1000);

			try {
				p.exitValue();
			} catch (IllegalStateException e) {
				e.printStackTrace();
				p.destroy();
			}
			ready = false;
			if (null == parser.getValues())
				throw new RuntimeException("Cannot Solve");
			for (Entry<String, String> entry : parser.getValues().entrySet()) {
				result.put(entry.getKey(), Integer.valueOf(entry.getValue()));
			}
			return result;
		} catch (Exception e) {
			if (e instanceof RuntimeException)
				throw (RuntimeException) e;
			throw new RuntimeException(e);
		}
	}

	public int getWidth() {
		return getSize() * getSize();
	}
}
