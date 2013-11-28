package clarkson.cs551.robocode.moving;

import java.awt.geom.Point2D;

import robocode.AdvancedRobot;
import robocode.ScannedRobotEvent;

public abstract class AbstractMovingHandler implements MovingHandler {

	@Override
	public void action(AdvancedRobot robot) {
		
	}
	
	protected abstract Point2D.Double estimate(AdvancedRobot robot);

	@Override
	public void enemyScanned(AdvancedRobot robot, ScannedRobotEvent event) {

	}

	@Override
	public void initialize(AdvancedRobot robot) {
		loadData(robot);
	}

	@Override
	public void loadData(AdvancedRobot robot) {
	}

	@Override
	public void storeData(AdvancedRobot robot) {
	}

}
