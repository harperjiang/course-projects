package clarkson.cs551.robocode.targeting;

import robocode.Bullet;
import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.ScannedRobotEvent;
import clarkson.cs551.BasicRobot;

public interface TargetingHandler {

	public void initialize(BasicRobot robot);

	public void enemyScanned(BasicRobot self, ScannedRobotEvent event);

	public void bulletFired(BasicRobot self, Bullet bullet);

	public void bulletHit(BasicRobot self, BulletHitEvent event);

	public void bulletMissed(BasicRobot self, BulletMissedEvent event);

	public void action(BasicRobot robot);

	public void bulletHitBullet(BasicRobot robot, BulletHitBulletEvent event);

	public AccuracySta getStatistic();

	public void storeData(BasicRobot robot);

	public void loadData(BasicRobot robot);

	public void clearBattleData(BasicRobot robot);

}
