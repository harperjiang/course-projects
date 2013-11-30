package clarkson.cs551.robocode.moving;

import java.awt.geom.Point2D;

import robocode.Rules;
import robocode.ScannedRobotEvent;
import robocode.util.Utils;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.common.GeometricUtils;
import clarkson.cs551.robocode.common.SimulationUtils;

public class AStarTreeHandler extends AbstractMovingHandler {

	private int factor;

	private double[] radians;

	private EnemyStatus lastStatus;

	public AStarTreeHandler() {
		super();
		factor = 1;
		initCosts();
	}

	private void initCosts() {
		radians = new double[factor * 4 + 4];
		double step = Math.PI / (2 * (factor + 1));
		for (int i = 0; i < factor + 1; i++) {
			radians[i] = i * step;
			radians[factor + 1 + i] = (factor + 1 - i) * step;
			radians[factor * 2 + 2 + i] = i * step;
			radians[factor * 3 + 3 + i] = (factor + 1 - i) * step;
		}
	}

	@Override
	protected Point2D.Double estimate(BasicRobot robot) {
		if (lastStatus == null)
			return null;
		// Take the time needed to do the move into account

		double[] cost = new double[radians.length];
		Point2D.Double[] expects = new Point2D.Double[cost.length];
		double step = Math.PI / (2 * (factor + 1));
		double heading = GeometricUtils.absoluteHeading(robot
				.getHeadingRadians());
		double time = lastStatus.getDistance() / Rules.getBulletSpeed(1d);

		for (int i = 0; i < cost.length; i++) {
			// Cost of turn
			cost[i] = -(int) Math
					.ceil(radians[i] / Rules.MAX_TURN_RATE_RADIANS);
			// calculate the heuristic for each point after movement
			expects[i] = estimateMove(robot, heading + step * i, time - cost[i]);
			cost[i] += heuristic(robot, expects[i], lastStatus);
		}
		// Look for the minimal value
		double val = 0;
		int index = -1;
		for (int i = 0; i < cost.length; i++) {
			if (cost[i] > val) {
				val = cost[i];
				index = i;
			}
		}
		// The choice is i
		return expects[index];
	}

	protected Point2D.Double estimateMove(BasicRobot robot, double dir,
			double time) {
		Point2D.Double currentPos = robot.getPosition();
		double distance = SimulationUtils.distance((int) time);
		Point2D.Double dest = new Point2D.Double(currentPos.x + Math.cos(dir)
				* distance, currentPos.y + Math.sin(dir) * distance);
		if (dest.x >= robot.getWidth() && dest.y >= robot.getWidth()
				&& dest.x <= robot.getBattleFieldWidth() - robot.getWidth()
				&& dest.y <= robot.getBattleFieldHeight() - robot.getWidth())
			return dest;

		double distx = 0;
		if (Math.cos(dir) > 0) {
			distx = Math
					.max((robot.getBattleFieldWidth() - robot.getWidth() - currentPos.x)
							/ Math.cos(dir), 0);
		} else {
			distx = Math.max(
					(currentPos.x - robot.getWidth()) / (-Math.cos(dir)), 0);
		}
		double disty = 0;
		if (Math.sin(dir) > 0) {
			disty = Math
					.max((robot.getBattleFieldHeight() - robot.getWidth() - currentPos.y)
							/ Math.sin(dir), 0);
		} else {
			disty = Math.max(
					(currentPos.y - robot.getWidth()) / (-Math.sin(dir)), 0);
		}
		double dist = Math.min(distx, disty);
		return new Point2D.Double(currentPos.x + Math.cos(dir) * dist,
				currentPos.y + Math.sin(dir) * dist);
	}

	protected double heuristic(BasicRobot robot, Point2D.Double expect,
			EnemyStatus enemyStatus) {
		// Boundary Check
		double size = Math.max(robot.getWidth(), robot.getHeight());
		double olddist = GeometricUtils.getDistance(robot.getPosition(),
				enemyStatus.getPosition());
		double newdist = GeometricUtils.getDistance(expect,
				enemyStatus.getPosition());
		double newangle = GeometricUtils.getRadian(enemyStatus.getPosition(),
				expect);
		double oldangle = GeometricUtils.getRadian(enemyStatus.getPosition(),
				robot.getPosition());
		double moving = GeometricUtils.getRadian(robot.getPosition(), expect);
		double looking = GeometricUtils.getRadian(robot.getPosition(),
				enemyStatus.getPosition());

		// Moving a long distance is preferred
		double value = GeometricUtils.getDistance(robot.getPosition(), expect);

		// If energy change indicate bullet fire
		if (enemyStatus.getEnergyChange() <= -0.1
				&& enemyStatus.getEnergyChange() >= -3.0) {
			double damage = Rules
					.getBulletDamage(enemyStatus.getEnergyChange());
			double distance = Math.sin(Math.abs(newangle - oldangle) * newdist);
			if (distance < size)
				value -= damage;
		}

		// Moving direction, moving orthgonal is preferred
		value += 500 * (1 - Math.abs(Math.cos(moving - looking)));

		// If too close that cannot dodge bullet
		double bulletTurn = newdist / Rules.getBulletSpeed(1.0d);
		double movable = SimulationUtils.distance((int) bulletTurn);
		// Moving faraway is preferred
		value += 10 * (newdist - olddist + movable);

		// TODO: If too far away cannot have good shooting rate

		return value;
	}

	@Override
	public void enemyScanned(BasicRobot robot, ScannedRobotEvent event) {
		EnemyStatus newstatus = new EnemyStatus();
		newstatus.setVelocity(event.getVelocity());

		double dist = event.getDistance();
		double bearing = event.getBearingRadians();
		double heading = GeometricUtils.absoluteHeading(robot
				.getHeadingRadians());
		double dir = Utils.normalAbsoluteAngle(heading - bearing);

		newstatus.setPosition(new Point2D.Double(Math.cos(dir) * dist
				+ robot.getPosition().x, Math.sin(dir) * dist
				+ robot.getPosition().y));

		newstatus.setDistance(dist);

		double energy = event.getEnergy();
		newstatus.setEnergy(energy);
		if (lastStatus != null) {
			newstatus.setEnergyChange(newstatus.getEnergy()
					- lastStatus.getEnergy());
		} else {
			newstatus.setEnergyChange(0);
		}

		lastStatus = newstatus;
		if (newstatus.getEnergyChange() != 0) {
			triggerInterrupt();
		}
	}

}
