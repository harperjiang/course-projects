package clarkson.cs551.robocode.targeting;

import java.awt.geom.Point2D;

import robocode.AdvancedRobot;
import robocode.Rules;
import clarkson.cs551.robocode.common.AbsolutePos;
import clarkson.cs551.robocode.common.GeometricUtils;

public class CircularHandler extends AbstractTargetingHandler {

	private double firePower = 2d;

	public CircularHandler() {
		super(3);
	}

	@Override
	protected FireResult estimate(AdvancedRobot robot) {
		// TODO Modify this
		AbsolutePos mypos = new AbsolutePos(0l, new Point2D.Double(0, 0), null);
		if (paths.size() < 3) {
			return null;
		}
		AbsolutePos p1 = paths.get(0);
		AbsolutePos p2 = paths.get(1);
		AbsolutePos p3 = paths.get(2);

		if (p2.getX() == p3.getX() && p2.getY() == p3.getY()) {
			// Deal with the not moving case
			return new FireResult(GeometricUtils.absoluteHeading(robot
					.getGunHeadingRadians())
					- GeometricUtils.getRadian(mypos.getPosition(),
							p3.getPosition()), firePower);
		}
		// x(2x0-2x1)+y(2y0-2y1) = x0^2+y0^2-x1^2-y1^2
		// x(2x1-2x2)+y(2x1-2x2) = x1^2+y1^2-x2^2-y2^2

		double a1 = 2 * (p1.getX() - p2.getX());
		double b1 = 2 * (p1.getY() - p2.getY());
		double c1 = Math.pow(p1.getX(), 2) + Math.pow(p1.getY(), 2)
				- Math.pow(p2.getX(), 2) - Math.pow(p2.getY(), 2);
		double a2 = 2 * (p2.getX() - p3.getX());
		double b2 = 2 * (p2.getY() - p3.getY());
		double c2 = Math.pow(p2.getX(), 2) + Math.pow(p2.getY(), 2)
				- Math.pow(p3.getX(), 2) - Math.pow(p3.getY(), 2);

		double y = (c1 * a2 - a1 * c2) / (b1 * a2 - a1 * b2);
		double x = (c1 - b1 * y) / a1;
		Point2D.Double center = new Point2D.Double(x, y);

		double a = Math.sqrt(Math.pow(x - p1.getX(), 2)
				+ Math.pow(y - p1.getY(), 2));

		double theta2 = GeometricUtils.getRadian(center, p2.getPosition());
		double theta3 = GeometricUtils.getRadian(center, p3.getPosition());

		double thetaspeed = (theta3 - theta2) / (p3.getTime() - p2.getTime());

		double bulletSpeed = Rules.getBulletSpeed(firePower);

		int maxt = 40;
		double step = 0.01;
		double tval = 0;
		double threshold = 0.1;
		Point2D.Double testp = p3.getPosition();
		// Use numerical to simulate time of hit
		while (tval < maxt) {
			double r = bulletSpeed * tval;
			double theta = theta3 + thetaspeed * tval;
			testp = new Point2D.Double(Math.cos(theta) * a + x, Math.sin(theta)
					* a + y);
			double val = Math.abs(r
					- GeometricUtils.getDistance(mypos.getPosition(), testp));

			if (val <= threshold)
				break;
			tval += step;
		}
		double direction = GeometricUtils.absoluteHeading(robot
				.getGunHeadingRadians())
				- GeometricUtils.getRadian(mypos.getPosition(), testp);
		if (tval < maxt) {
			return new FireResult(direction, firePower);
		} else {
			// Exceed Prediction
		}
		return null;
	}
}
