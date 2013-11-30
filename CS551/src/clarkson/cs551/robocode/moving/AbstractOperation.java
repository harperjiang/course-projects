package clarkson.cs551.robocode.moving;

import clarkson.cs551.BasicRobot;

public abstract class AbstractOperation implements Operation {

	private boolean submitted = false;

	@Override
	public void execute(BasicRobot robot) {
		submitted = true;
	}

	@Override
	public boolean submitted() {
		return submitted;
	}

}
