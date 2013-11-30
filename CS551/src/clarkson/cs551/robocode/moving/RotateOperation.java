package clarkson.cs551.robocode.moving;

import clarkson.cs551.BasicRobot;

public class RotateOperation extends AbstractOperation {

	private BasicRobot robot;

	private double angle;

	public RotateOperation(double angle) {
		super();
		this.angle = angle;
	}

	@Override
	public void execute(BasicRobot robot) {
		this.robot = robot;
		if (Math.abs(angle) <= Math.PI / 2) {
			robot.setTurnLeftRadians(angle);
		} else {
			double rotate = Math.PI - Math.abs(angle);
			if (angle > 0) {
				robot.setTurnRightRadians(rotate);
			} else {
				robot.setTurnLeftRadians(rotate);
			}
		}
		super.execute(robot);
	}

	@Override
	public boolean done() {
		return this.robot.getTurnRemainingRadians() == 0;
	}

}
