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

		long[] cost = new long[radians.length];
		Point2D.Double[] expects = new Point2D.Double[cost.length];
		double step = Math.PI / (2 * (factor + 1));
		double heading = GeometricUtils.absoluteHeading(robot
				.getHeadingRadians());
		double time = lastStatus.getDistance() / Rules.getBulletSpeed(1d);

		// System.out.println("Current Position is:" + robot.getPosition());
		for (int i = 0; i < cost.length; i++) {
			// Cost of turn
			cost[i] = (int) Math.ceil(radians[i] / Rules.MAX_TURN_RATE_RADIANS);
			// System.out.println("Cost " + i + " is " + cost[i]);
			// calculate the heuristic for each point after movement
			expects[i] = estimateMove(robot, heading + step * i, time - cost[i]);
			cost[i] += heuristic(robot, expects[i], lastStatus);
			// System.out.println("Choice " + i + " is " + expects[i]);
			// System.out.println("Total " + i + " is " + cost[i]);
		}
		// Look for the minimal value
		long val = Long.MAX_VALUE;
		int index = -1;
		for (int i = 0; i < cost.length; i++) {
			if (cost[i] < val) {
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
		return new Point2D.Double(currentPos.x + Math.cos(dir) * distance,
				currentPos.y + Math.sin(dir) * distance);
	}

	protected long heuristic(BasicRobot robot, Point2D.Double expect,
			EnemyStatus enemyStatus) {
		// Boundary Check
		double size = Math.max(robot.getWidth(), robot.getHeight());
		double newdist = GeometricUtils.getDistance(expect,
				enemyStatus.getPosition());
		double newangle = GeometricUtils.getRadian(enemyStatus.getPosition(),
				expect);
		double oldangle = GeometricUtils.getRadian(enemyStatus.getPosition(),
				robot.getPosition());

		if (expect.getX() <= size || expect.getY() <= size
				|| expect.getX() >= robot.getBattleFieldWidth() - size
				|| expect.getY() >= robot.getBattleFieldHeight() - size)
			return Integer.MAX_VALUE;

		long value = 0;

		// If energy change indicate bullet fire
		if (enemyStatus.getEnergyChange() >= 0.1
				&& enemyStatus.getEnergyChange() <= 3.0) {
			double damage = Rules
					.getBulletDamage(enemyStatus.getEnergyChange());

			double distance = Math.sin(Math.abs(newangle - oldangle) * newdist);
			if (distance < size)
				value += (100 - robot.getEnergy()) / damage;
		}

		// If too close that cannot dodge bullet
		double bulletTurn = newdist / Rules.getBulletSpeed(1.0d);
		double movable = SimulationUtils.distance((int) bulletTurn);
		value += (robot.getBattleFieldWidth() - movable) / size;

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
	}

}
