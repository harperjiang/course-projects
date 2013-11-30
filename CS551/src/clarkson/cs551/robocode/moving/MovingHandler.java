package clarkson.cs551.robocode.moving;

import robocode.ScannedRobotEvent;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.Handler;

public interface MovingHandler extends Handler {

	void enemyScanned(BasicRobot robot, ScannedRobotEvent event);

}
