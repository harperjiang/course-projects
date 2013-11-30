package clarkson.cs551.robocode;

import robocode.BattleEndedEvent;
import robocode.ScannedRobotEvent;
import robocode.StatusEvent;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.moving.AStarTreeHandler;
import clarkson.cs551.robocode.moving.MovingHandler;
import clarkson.cs551.robocode.radar.LockingHandler;
import clarkson.cs551.robocode.radar.RadarHandler;

public class MovingRobot extends BasicRobot {

	private RadarHandler radarHandler;

	private MovingHandler movingHandler;

	public MovingRobot() {
		super();
		radarHandler = new LockingHandler();
		movingHandler = new AStarTreeHandler();
		movingHandler.initialize(this);
	}

	@Override
	public void run() {
		while (true) {
			radarHandler.action(this);
			movingHandler.action(this);
			execute();
		}
	}

	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		radarHandler.enemyScanned(this, event);
		movingHandler.enemyScanned(this, event);
	}

	@Override
	public void onBattleEnded(BattleEndedEvent event) {
		movingHandler.storeData(this);
	}
	
	@Override
	public void onStatus(StatusEvent e) {
		super.onStatus(e);
	}

}
