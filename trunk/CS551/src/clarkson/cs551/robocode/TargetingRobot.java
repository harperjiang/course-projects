package clarkson.cs551.robocode;

import robocode.AdvancedRobot;
import robocode.ScannedRobotEvent;
import clarkson.cs551.robocode.moving.Coordinate;
import clarkson.cs551.robocode.radar.LockingHandler;
import clarkson.cs551.robocode.radar.RadarHandler;
import clarkson.cs551.robocode.targeting.LinearTargetingHandler;
import clarkson.cs551.robocode.targeting.TargetingHandler;

public class TargetingRobot extends AdvancedRobot {

	private RadarHandler radarHandler;

	private TargetingHandler targetingHandler;
	
	private Coordinate coordinate;

	public TargetingRobot() {
		super();
		radarHandler = new LockingHandler();
		targetingHandler = new LinearTargetingHandler();
	}

	@Override
	public void run() {
		while (true) {
			radarHandler.action(this);
			targetingHandler.action(this);
			execute();
		}
	}

	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		radarHandler.enemyScanned(this, event);
		targetingHandler.enemyScanned(this, event);
	}
}
