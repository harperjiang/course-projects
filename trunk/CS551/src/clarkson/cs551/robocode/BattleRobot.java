package clarkson.cs551.robocode;

import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.RoundEndedEvent;
import robocode.ScannedRobotEvent;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.moving.AStarTreeHandler;
import clarkson.cs551.robocode.moving.MovingHandler;
import clarkson.cs551.robocode.radar.LockingHandler;
import clarkson.cs551.robocode.radar.RadarHandler;
import clarkson.cs551.robocode.targeting.MixedTargetingHandler;
import clarkson.cs551.robocode.targeting.TargetingHandler;

public class BattleRobot extends BasicRobot {
	private RadarHandler radarHandler;

	private TargetingHandler targetingHandler;

	private MovingHandler movingHandler;

	public BattleRobot() {
		super();
		radarHandler = new LockingHandler();
		targetingHandler = new MixedTargetingHandler();
		movingHandler = new AStarTreeHandler();

		movingHandler.initialize(this);
		targetingHandler.initialize(this);
	}

	@Override
	public void run() {
		while (true) {
			radarHandler.action(this);
			movingHandler.action(this);
			targetingHandler.action(this);
			execute();
		}
	}

	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		radarHandler.enemyScanned(this, event);
		movingHandler.enemyScanned(this, event);
		targetingHandler.enemyScanned(this, event);
	}

	@Override
	public void onBulletHit(BulletHitEvent event) {
		targetingHandler.bulletHit(this, event);
	}

	@Override
	public void onBulletHitBullet(BulletHitBulletEvent event) {
		targetingHandler.bulletHitBullet(this, event);
	}

	@Override
	public void onBulletMissed(BulletMissedEvent event) {
		targetingHandler.bulletMissed(this, event);
	}

	@Override
	public void onRoundEnded(RoundEndedEvent event) {
		targetingHandler.storeData(this);
		movingHandler.storeData(this);
	}
}
