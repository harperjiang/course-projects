package clarkson.cs551;

import clarkson.cs551.robocode.common.SimulationUtils;

public class TestMovementRobot extends BasicRobot {
	@Override
	public void run() {
		while (true) {
			System.out.println("Turn " + getTime());
			if (getTime() == 0) {
				setAhead(39);
			}
			if (getTime() == 4) {
				setAhead(0);
			}
			System.out.println("Current Speed:" + getVelocity());
			System.out.println("Remaining Dist:" + getDistanceRemaining());
			System.out.println("Estimate Speed:"
					+ (SimulationUtils.simulate(getDistanceRemaining(),
							getVelocity())));
			execute();
		}
	}
}
