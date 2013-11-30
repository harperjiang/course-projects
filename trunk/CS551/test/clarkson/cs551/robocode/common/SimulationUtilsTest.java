package clarkson.cs551.robocode.common;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class SimulationUtilsTest {

	@Test
	public void testSimulate() {
		assertEquals(6, SimulationUtils.simulate(12, 6), 0.01);
		assertEquals(4, SimulationUtils.simulate(6, 6), 0.01);
		assertEquals(17d / 3, SimulationUtils.simulate(11, 7), 0.01);
	}

	@Test
	public void testDistance() {
		assertEquals(39, SimulationUtils.distance(10), 0.01);
		assertEquals(40, SimulationUtils.distance(11), 0.01);
	}
}
