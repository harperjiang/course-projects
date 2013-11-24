package clarkson.cs551.robocode;

import robocode.AdvancedRobot;
import robocode.ScannedRobotEvent;
import clarkson.cs551.robocode.radar.LockingHandler;
import clarkson.cs551.robocode.radar.RadarHandler;

public class TargetingRobot extends AdvancedRobot {

	private RadarHandler radarHandler;

	public TargetingRobot() {
		super();
		radarHandler = new LockingHandler();
	}

	@Override
	public void run() {
		while (true) {
			radarHandler.action(this);
			execute();
		}
	}

	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		radarHandler.enemyScanned(this, event);
	}

}
