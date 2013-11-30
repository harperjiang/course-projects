package clarkson.cs551.robocode;

import robocode.BattleEndedEvent;
import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.RoundEndedEvent;
import robocode.ScannedRobotEvent;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.radar.LockingHandler;
import clarkson.cs551.robocode.radar.RadarHandler;
import clarkson.cs551.robocode.targeting.MixedTargetingHandler;
import clarkson.cs551.robocode.targeting.TargetingHandler;

public class TargetingRobot extends BasicRobot {

	private RadarHandler radarHandler;

	private TargetingHandler targetingHandler;

	public TargetingRobot() {
		super();
		radarHandler = new LockingHandler();
		targetingHandler = new MixedTargetingHandler();

		targetingHandler.initialize(this);
	}

	@Override
	public void run() {
		while (true) {
			radarHandler.action(this);
			targetingHandler.action(this);
			execute();
		}
	}

	@Override
	public void onScannedRobot(ScannedRobotEvent event) {
		radarHandler.enemyScanned(this, event);
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
	}
}
