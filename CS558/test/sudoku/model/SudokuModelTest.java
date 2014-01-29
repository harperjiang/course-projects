package sudoku.model;

import static org.junit.Assert.assertTrue;

import java.text.MessageFormat;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import org.junit.Test;

import common.exec.z3.Z3Executor;

public class SudokuModelTest {

	@Test
	public void testGenerate() {
		SudokuModel model = new SudokuModel(2);

		Map<String, Object> assignment = new HashMap<String, Object>();
		boolean sat = new Z3Executor().execute(model, assignment);

		assertTrue(sat);
		for (Entry<String, Object> assign : assignment.entrySet()) {
			System.out.println(MessageFormat.format("{0}={1}", assign.getKey(),
					assign.getValue()));
		}
	}

}
