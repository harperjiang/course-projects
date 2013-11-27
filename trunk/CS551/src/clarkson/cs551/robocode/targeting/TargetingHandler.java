package clarkson.cs551.robocode.targeting;

import robocode.AdvancedRobot;
import robocode.Bullet;
import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.ScannedRobotEvent;

public interface TargetingHandler {
	
	public void initialize(AdvancedRobot robot);

	public void enemyScanned(AdvancedRobot self, ScannedRobotEvent event);

	public void bulletFired(Bullet bullet);

	public void bulletHit(AdvancedRobot self, BulletHitEvent event);

	public void bulletMissed(AdvancedRobot self, BulletMissedEvent event);

	public void action(AdvancedRobot robot);

	public void bulletHitBullet(AdvancedRobot robot, BulletHitBulletEvent event);

	public void storeData(AdvancedRobot robot);

	public void loadData(AdvancedRobot robot);

}
