package clarkson.cs551.robocode;

import clarkson.cs551.BasicRobot;

public interface Handler {

	void action(BasicRobot robot);

	void initialize(BasicRobot robot);

	void loadData(BasicRobot robot);

	void storeData(BasicRobot robot);
}
