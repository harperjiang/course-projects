package clarkson.cs551.robocode.moving;

import clarkson.cs551.BasicRobot;

public interface Operation {

	public void execute(BasicRobot robot);

	public boolean submitted();

	public boolean done();
}
