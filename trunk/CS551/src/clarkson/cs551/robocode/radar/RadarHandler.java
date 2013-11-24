package clarkson.cs551.robocode.radar;

import robocode.AdvancedRobot;
import robocode.ScannedRobotEvent;

public interface RadarHandler {

	public void enemyScanned(AdvancedRobot self, ScannedRobotEvent event);

	public void action(AdvancedRobot robot);
}
