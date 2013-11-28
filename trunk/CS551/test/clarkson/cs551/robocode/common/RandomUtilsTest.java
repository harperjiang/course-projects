package clarkson.cs551.robocode.common;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.List;

import org.junit.Test;

public class RandomUtilsTest {

	@Test
	public void testRandomChoose() {
		List<Double> test = new ArrayList<Double>();
		test.add(1d);
		test.add(2d);
		test.add(0.5d);
		for (int i = 0; i < 100; i++)
			assertTrue(-1 != RandomUtils.randomChoose(test));
	}

}
