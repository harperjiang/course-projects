package clarkson.cs551.robocode.targeting;

import java.awt.geom.Point2D;

import robocode.Rules;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.common.AbsolutePos;
import clarkson.cs551.robocode.common.GeometricUtils;
import clarkson.cs551.robocode.common.Velocity;

public class LinearHandler extends AbstractTargetingHandler {

	private int firePower = 2;

	public LinearHandler() {
		super(3);
	}

	@Override
	protected FireResult estimate(BasicRobot robot) {
		Point2D.Double mypos = robot.getPosition();
		if (paths.size() < 2) {
			return null;
		}
		AbsolutePos p2 = paths.get(0);
		AbsolutePos p3 = paths.get(1);

		double vx = (p3.getX() - p2.getX()) / (p3.getTime() - p2.getTime());
		double vy = (p3.getY() - p2.getY()) / (p3.getTime() - p2.getTime());

		double bulletSpeed = Rules.getBulletSpeed(firePower);

		double a = Math.pow(bulletSpeed, 2) - Math.pow(vx, 2) - Math.pow(vy, 2);
		double b = -2 * vx * p3.getX() - 2 * vy * p3.getY();
		double c = -Math.pow(p3.getX(), 2) - Math.pow(p3.getY(), 2);

		double t = (-b + Math.sqrt(Math.pow(b, 2) - 4 * a * c)) / (2 * a);

		// (x3+vx*t)^2+(y3+vy*t)^2) = t^2* bulletSpeed^2
		if (enableLogging)
			System.out.println("Estimate time to hit:" + t);

		Point2D.Double velopoint = new Point2D.Double(vx, vy);

		AbsolutePos newp = new AbsolutePos(p3.getTime() + (long) Math.ceil(t),
				new Point2D.Double(p3.getX() + vx * t, p3.getY() + vy * t),
				mypos, new Velocity(GeometricUtils.getRadian(velopoint),
						GeometricUtils.getDistance(velopoint)));
		if (enableLogging)
			System.out.println("New Point will be:" + newp);

		double radian = GeometricUtils.getRadian(mypos, newp.getPosition());
		double gunHeading = GeometricUtils.absoluteHeading(robot
				.getGunHeadingRadians());
		return new FireResult(gunHeading - radian, firePower);
	}
}
