package clarkson.cs551.robocode.targeting;

import java.awt.geom.Point2D;
import java.util.Random;

import robocode.AdvancedRobot;
import robocode.Rules;
import clarkson.cs551.robocode.common.AbsolutePos;
import clarkson.cs551.robocode.common.GeometricUtils;

public class GuessFactorHandler extends AbstractTargetingHandler {

	public GuessFactorHandler() {
		super(30);
		summary = new int[interval];
		random = new Random(System.currentTimeMillis());
	}

	private int interval = 10;

	private int[] summary;

	private Random random;

	@Override
	protected FireResult estimate(AdvancedRobot robot) {
		int sum = 0;
		for (int i = 0; i < summary.length; i++)
			sum += summary[i];
		if (sum == 0)
			return null;
		random.nextInt(sum);
		int i = 0;
		int current = summary[i];
		while (current < sum) {
			i++;
			current += summary[i];
		}
		// Fire to interval i
		AbsolutePos last = paths.get(paths.size() - 1);
		double distance = GeometricUtils.getDistance(last.getMyPosition(),
				last.getPosition());
		double bulletSpeed = Rules.getBulletSpeed(2);
		long bulletTime = (long) Math.ceil(distance / bulletSpeed);
		double dx = bulletTime * last.getVelocity().getVx();
		double dy = bulletTime * last.getVelocity().getVy();
		double maxTheta = GeometricUtils.getRadian(last.getMyPosition(),
				new Point2D.Double(last.getX() + dx, last.getY() + dy));
		double minTheta = GeometricUtils.getRadian(last.getMyPosition(),
				new Point2D.Double(last.getX() - dx, last.getY() - dy));

		double fireDirection = minTheta
				+ ((maxTheta - minTheta) * i / interval);
		return new FireResult(GeometricUtils.absoluteHeading(robot
				.getGunHeading()) - fireDirection, 2d);
	}

	@Override
	protected void onNewPath(AbsolutePos path) {
		if (paths.size() < 2)
			return;

		AbsolutePos from = paths.get(paths.size() - 2);
		AbsolutePos to = paths.get(paths.size() - 1);

		long time = to.getTime() - from.getTime();
		double dx = time * from.getVelocity().getVx();
		double dy = time * to.getVelocity().getVy();

		double maxTheta = GeometricUtils.getRadian(from.getMyPosition(),
				new Point2D.Double(from.getX() + dx, from.getY() + dy));
		double minTheta = GeometricUtils.getRadian(from.getMyPosition(),
				new Point2D.Double(from.getX() - dx, from.getY() - dy));
		double actualTheta = GeometricUtils.getRadian(from.getMyPosition(),
				to.getPosition());

		double step = (maxTheta - minTheta) / interval;
		int in = (int) Math.floor((actualTheta - minTheta) / step);
		summary[in] += 1;
	}
}
