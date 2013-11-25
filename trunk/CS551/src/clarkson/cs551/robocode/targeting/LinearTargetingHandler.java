package clarkson.cs551.robocode.targeting;

import java.awt.geom.Point2D;

import robocode.AdvancedRobot;
import robocode.Rules;
import clarkson.cs551.robocode.common.AbsolutePos;
import clarkson.cs551.robocode.common.GeometricUtils;

public class LinearTargetingHandler extends AbstractTargetingHandler {

	private int firePower = 2;

	public LinearTargetingHandler() {
		super(3);
	}

	@Override
	protected FireResult estimate(AdvancedRobot robot) {
		// TODO Modify this
		AbsolutePos mypos = new AbsolutePos(0l, new Point2D.Double(0, 0));
		if (paths.size() < 3) {
			return null;
		}
		AbsolutePos p2 = paths.get(1);
		AbsolutePos p3 = paths.get(2);

		double vx = (p3.getX() - p2.getX()) / (p3.getTime() - p2.getTime());
		double vy = (p3.getY() - p2.getY()) / (p3.getTime() - p2.getTime());

		double bulletSpeed = Rules.getBulletSpeed(firePower);

		double a = Math.pow(bulletSpeed, 2) - Math.pow(vx, 2) - Math.pow(vy, 2);
		double b = -2 * vx * p3.getX() - 2 * vy * p3.getY();
		double c = -Math.pow(p3.getX(), 2) - Math.pow(p3.getY(), 2);

		double t = (-b + Math.sqrt(Math.pow(b, 2) - 4 * a * c)) / (2 * a);

		// (x3+vx*t)^2+(y3+vy*t)^2) = t^2* bulletSpeed^2

		System.out.println("Estimate time to hit:" + t);

		AbsolutePos newp = new AbsolutePos(p3.getTime() + (long) Math.ceil(t),
				new Point2D.Double(p3.getX() + vx * t, p3.getY() + vy * t));

		System.out.println("New Point will be:" + newp);

		double radian = GeometricUtils.getRadian(mypos, newp);
		double gunHeading = GeometricUtils.absoluteHeading(robot
				.getGunHeadingRadians());
		if (Math.abs(gunHeading - radian) <= Rules.GUN_TURN_RATE_RADIANS) {
			// Enough time to turn gun to position
			// TODO Take my position into account
			return new FireResult(gunHeading - radian, firePower);
		}
		// Just turn gun as much as possible
		if ((radian >= gunHeading && Math.abs(radian - gunHeading) < Math.PI)
				|| ((radian < gunHeading) && (Math.abs(radian - gunHeading) > Math.PI))) {
			return new FireResult(-Rules.GUN_TURN_RATE_RADIANS, firePower);
		} else {
			return new FireResult(Rules.GUN_TURN_RATE_RADIANS, 0d);
		}
	}
}
