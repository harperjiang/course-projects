package clarkson.cs551.robocode.targeting;

import robocode.AdvancedRobot;
import robocode.ScannedRobotEvent;

public interface TargetingHandler {

	public void enemyScanned(AdvancedRobot self, ScannedRobotEvent event);

	public void action(AdvancedRobot robot);

}
