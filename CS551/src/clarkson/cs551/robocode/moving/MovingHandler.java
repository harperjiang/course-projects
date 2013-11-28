package clarkson.cs551.robocode.moving;

import robocode.AdvancedRobot;
import robocode.ScannedRobotEvent;
import clarkson.cs551.robocode.Handler;

public interface MovingHandler extends Handler {

	void enemyScanned(AdvancedRobot robot, ScannedRobotEvent event);

}
