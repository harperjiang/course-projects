package common.exec.z3;

import org.junit.Test;

import checkboard.model.NormalModel;

public class Z3ExecutorTest {

	@Test
	public void testExecute() {
		new Z3Executor().execute(new NormalModel(4, 4), null);
	}

}
