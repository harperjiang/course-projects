package clarkson.cs551.robocode.targeting;

import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.List;

import robocode.AdvancedRobot;
import robocode.ScannedRobotEvent;
import robocode.util.Utils;
import clarkson.cs551.robocode.common.AbsolutePos;
import clarkson.cs551.robocode.common.GeometricUtils;

public abstract class AbstractTargetingHandler implements TargetingHandler {

	protected List<AbsolutePos> paths;

	protected int pathLength;

	private int pathInterval = 2;

	public AbstractTargetingHandler(int length) {
		this.pathLength = length;
		this.paths = new ArrayList<AbsolutePos>();
	}

	@Override
	public void enemyScanned(AdvancedRobot self, ScannedRobotEvent event) {
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
		System.out.println(pos);
		paths.add(pos);
	}

	protected AbsolutePos generatePos(AdvancedRobot robot,
			ScannedRobotEvent event) {
		// TODO Temporarily assume that robot doesn't move
		double bearing = event.getBearingRadians();
		double heading = GeometricUtils.absoluteHeading(robot
				.getHeadingRadians());
		double direction = Utils.normalAbsoluteAngle(heading - bearing);
		double distance = event.getDistance();
		return new AbsolutePos(robot.getTime(), new Point2D.Double(distance
				* Math.cos(direction), distance * Math.sin(direction)));
	}

	@Override
	public void action(AdvancedRobot robot) {
		double gunHeading = GeometricUtils.absoluteHeading(robot
				.getGunHeadingRadians());
		// Calculate the next position
		FireResult result = estimate(robot);
		if (result == null) {
			return;
		}

		double gunToHeading = result.getFireDirection();
		System.out.println("Current Gun Heading:" + gunHeading);
		System.out.println("Turn right of " + gunToHeading);
		robot.setTurnGunRightRadians(result.getFireDirection());
		// Adjust the radar position for locking
		robot.setTurnRadarRightRadians(robot.getRadarTurnRemainingRadians()
				- result.getFireDirection());
		System.out.println("Robot Gun Heat "+ robot.getGunHeat());
		System.out.println("Fire power "+ result.getFirePower());
		if (robot.getGunHeat() == 0 && result.getFirePower() > 0) {
			robot.setFire(result.getFirePower());
			System.out.println("Fired");
		}
		return;
	}

	protected abstract FireResult estimate(AdvancedRobot robot);

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
}
