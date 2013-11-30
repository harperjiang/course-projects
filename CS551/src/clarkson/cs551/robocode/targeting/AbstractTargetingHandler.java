package clarkson.cs551.robocode.targeting;

import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;

import robocode.Bullet;
import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.Rules;
import robocode.ScannedRobotEvent;
import robocode.util.Utils;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.common.AbsolutePos;
import clarkson.cs551.robocode.common.GeometricUtils;
import clarkson.cs551.robocode.common.Velocity;

public abstract class AbstractTargetingHandler implements TargetingHandler {

	protected List<AbsolutePos> paths;

	protected int pathLength;

	private int pathInterval = 1;

	private AccuracySta statistic;

	protected boolean enableLogging = false;

	public AbstractTargetingHandler(int length) {
		this.pathLength = length;
		this.paths = new ArrayList<AbsolutePos>();
		this.statistic = new AccuracySta();
	}

	@Override
	public void initialize(BasicRobot robot) {
		loadData(robot);
	}

	@Override
	public void enemyScanned(BasicRobot self, ScannedRobotEvent event) {
		// Set the minimal interval of data collected
		long lastTime = -pathInterval;
		if (paths.size() > 0) {
			lastTime = paths.get(paths.size() - 1).getTime();
		}
		if (self.getTime() - lastTime < pathInterval) {
			return;
		}
		// Clear path history if not enough space
		if (paths.size() == pathLength) {
			paths.remove(0);
		}
		AbsolutePos pos = generatePos(self, event);
		if (enableLogging)
			System.out.println(pos);
		paths.add(pos);
		onNewPath(pos);
	}

	protected AbsolutePos generatePos(BasicRobot robot, ScannedRobotEvent event) {
		double bearing = event.getBearingRadians();
		double heading = GeometricUtils.absoluteHeading(robot
				.getHeadingRadians());
		double enemyHeading = GeometricUtils.absoluteHeading(event
				.getHeadingRadians());
		double direction = Utils.normalAbsoluteAngle(heading - bearing);
		double distance = event.getDistance();
		Point2D.Double mypos = robot.getPosition();
		return new AbsolutePos(robot.getTime(), new Point2D.Double(distance
				* Math.cos(direction) + mypos.x, distance * Math.sin(direction)
				+ mypos.y), mypos, new Velocity(enemyHeading,
				event.getVelocity()));
	}

	@Override
	public void action(BasicRobot robot) {
		// Calculate the next position
		FireResult result = estimate(robot);
		if (result == null) {
			return;
		}

		double gunToHeading = result.getFireDirection();
		if (Math.abs(gunToHeading) <= Rules.GUN_TURN_RATE_RADIANS) {
			// Enough time to turn gun to position
			// TODO Take my position into account
			turnRight(robot, result.getFireDirection());
			if (robot.getGunHeat() == 0 && result.getFirePower() > 0) {
				Bullet bullet = robot.setFireBullet(result.getFirePower());
				this.bulletFired(robot, bullet);
			}
		} else {
			// Just turn gun as much as possible
			if ((Math.abs(gunToHeading) < Math.PI && gunToHeading >= 0)
					|| (Math.abs(gunToHeading) > Math.PI && gunToHeading < 0)) {
				turnRight(robot, Rules.GUN_TURN_RATE_RADIANS);
			} else {
				turnRight(robot, -Rules.GUN_TURN_RATE_RADIANS);
			}
		}
		return;
	}

	public AccuracySta getStatistic() {
		return statistic;
	}

	protected void turnRight(BasicRobot robot, double value) {
		robot.setTurnGunRightRadians(value);
	}

	protected void onNewPath(AbsolutePos path) {

	}

	protected abstract FireResult estimate(BasicRobot robot);

	public static final class FireResult {

		double fireDirection;

		double firePower;

		public FireResult(double radius, double power) {
			this.fireDirection = radius;
			this.firePower = power;
		}

		public double getFireDirection() {
			return fireDirection;
		}

		public void setFireDirection(double fireDirection) {
			this.fireDirection = fireDirection;
		}

		public double getFirePower() {
			return firePower;
		}

		public void setFirePower(double firePower) {
			this.firePower = firePower;
		}
	}

	@Override
	public void storeData(BasicRobot robot) {

	}

	@Override
	public void loadData(BasicRobot robot) {

	}

	@Override
	public void bulletFired(BasicRobot robot, Bullet bullet) {
		AbsolutePos target = paths.get(paths.size() - 1);
		double distance = GeometricUtils.getDistance(target.getMyPosition(),
				target.getPosition());
		int equiv = (int) (distance / robot.getWidth());
		statistic.fired(equiv);
	}

	@Override
	public void bulletHit(BasicRobot self, BulletHitEvent event) {
		statistic.hit();
	}

	@Override
	public void bulletMissed(BasicRobot self, BulletMissedEvent event) {
		statistic.missed();
	}

	@Override
	public void bulletHitBullet(BasicRobot robot, BulletHitBulletEvent event) {
		statistic.missed();
	}
}
