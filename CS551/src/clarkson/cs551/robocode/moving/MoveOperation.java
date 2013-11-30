package clarkson.cs551.robocode.moving;

import clarkson.cs551.BasicRobot;

public class MoveOperation extends AbstractOperation {

	private BasicRobot robot;
	private double distance;
	private boolean ahead;

	public MoveOperation(double distance, boolean ahead) {
		super();
		this.distance = distance;
		this.ahead = ahead;
	}

	@Override
	public void execute(BasicRobot robot) {
		this.robot = robot;
		if (ahead) {
			robot.setAhead(distance);
		} else {
			robot.setBack(distance);
		}
		super.execute(robot);
	}

	@Override
	public boolean done() {
		return robot.getDistanceRemaining() == 0;
	}

}
