package clarkson.cs551.robocode.targeting;

import java.awt.geom.Point2D;
import java.util.Random;

import robocode.Rules;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.common.AbsolutePos;
import clarkson.cs551.robocode.common.GeometricUtils;

public class GuessFactorHandler extends AbstractTargetingHandler {

	public GuessFactorHandler() {
		super(30);
		summary = new int[interval];
		random = new Random(System.currentTimeMillis());
	}

	private double firePower = 2;

	private int interval = 10;

	private int[] summary;

	private Random random;

	@Override
	protected FireResult estimate(BasicRobot robot) {
		System.out.println("Fire Prediction");
		int sum = 0;
		for (int i = 0; i < summary.length; i++)
			sum += summary[i];
		if (sum == 0) {
			System.out.println("No data");
			return null;
		}
		random.nextInt(sum);
		int i = 0;
		int current = summary[i];
		while (current < sum) {
			i++;
			current += summary[i];
		}
		System.out.println("Fire to interval:" + i);
		// Fire to interval i
		AbsolutePos last = paths.get(paths.size() - 1);
		double distance = GeometricUtils.getDistance(last.getMyPosition(),
				last.getPosition());
		double bulletSpeed = Rules.getBulletSpeed(firePower);
		long bulletTime = (long) Math.ceil(distance / bulletSpeed);
		double dx = bulletTime * last.getVelocity().getVx();
		double dy = bulletTime * last.getVelocity().getVy();
		double maxTheta = GeometricUtils.getRadian(last.getMyPosition(),
				new Point2D.Double(last.getX() + dx, last.getY() + dy));
		double minTheta = GeometricUtils.getRadian(last.getMyPosition(),
				new Point2D.Double(last.getX() - dx, last.getY() - dy));
		System.out.println("Estimate max theta is " + maxTheta);
		System.out.println("Estimate min theta is " + minTheta);
		double fireDirection = minTheta
				+ ((maxTheta - minTheta) * i / interval);
		System.out.println("Estimate direction is " + fireDirection);
		System.out
				.println("Direction is "
						+ (GeometricUtils.absoluteHeading(robot.getGunHeading()) - fireDirection));
		return new FireResult(GeometricUtils.absoluteHeading(robot
				.getGunHeadingRadians()) - fireDirection, firePower);
	}

	@Override
	protected void onNewPath(AbsolutePos path) {
		if (paths.size() < 2)
			return;

		System.out.println("Data collection");
		AbsolutePos from = paths.get(paths.size() - 2);
		AbsolutePos to = paths.get(paths.size() - 1);

		long time = to.getTime() - from.getTime();
		double dx = time * from.getVelocity().getVx();
		double dy = time * from.getVelocity().getVy();

		System.out.println("Dx is " + dx);
		System.out.println("Dy is " + dy);

		double maxTheta = GeometricUtils.getRadian(from.getMyPosition(),
				new Point2D.Double(from.getX() + dx, from.getY() + dy));
		System.out.println("Max Theta:" + maxTheta);
		double minTheta = GeometricUtils.getRadian(from.getMyPosition(),
				new Point2D.Double(from.getX() - dx, from.getY() - dy));
		System.out.println("Min Theta:" + minTheta);
		double actualTheta = GeometricUtils.getRadian(from.getMyPosition(),
				to.getPosition());
		if (actualTheta > maxTheta)
			actualTheta = maxTheta;
		if (actualTheta < minTheta)
			actualTheta = minTheta;
		System.out.println("Actual Theta:" + actualTheta);

		double step = (maxTheta - minTheta) / interval;
		System.out.println("Step is " + step);
		int in = (int) Math.floor((actualTheta - minTheta) / step);
		if (in == interval)
			in = interval - 1;
		System.out.println("Interval:" + in);
		summary[in] += 1;
	}
}
