package clarkson.cs551.robocode;

import robocode.AdvancedRobot;

public interface Handler {

	void action(AdvancedRobot robot);

	void initialize(AdvancedRobot robot);

	void loadData(AdvancedRobot robot);

	void storeData(AdvancedRobot robot);
}
