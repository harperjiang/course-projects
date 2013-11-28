package clarkson.cs551.robocode;

import robocode.AdvancedRobot;
import robocode.ScannedRobotEvent;

public class TestCircularRobot extends AdvancedRobot {
	@Override
	public void run() {
		while (true) {
			setTurnRightRadians(Math.PI / 16);
			setAhead(20);
			execute();
		}
	}

	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		setFire(1);
	}

}
