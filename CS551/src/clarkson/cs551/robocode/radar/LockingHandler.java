package clarkson.cs551.robocode.radar;

import robocode.AdvancedRobot;
import robocode.Rules;
import robocode.ScannedRobotEvent;
import robocode.util.Utils;
import clarkson.cs551.robocode.common.RelativePos;

public class LockingHandler implements RadarHandler {

	private RelativePos lastPosition;

	@Override
	public void enemyScanned(AdvancedRobot self, ScannedRobotEvent event) {
		System.out.println("Scanned");
		lastPosition = new RelativePos(self.getHeadingRadians()
				+ event.getBearingRadians(), event.getDistance());
	}

	@Override
	public void action(AdvancedRobot robot) {
		if (null == lastPosition) {
			System.out.println("No target");
			robot.setTurnRadarRightRadians(2 * Math.PI);
			return;
		}
		System.out.println("Target acquired");
		double radarStart = robot.getRadarHeadingRadians();
		double target = lastPosition.getDirection();
		double turn = Utils.normalRelativeAngle(target - radarStart);
		double extraTurn = Math.min(
				Math.atan(36.0 / lastPosition.getDistance()),
				Rules.RADAR_TURN_RATE_RADIANS);
		turn += turn > 0 ? extraTurn : -extraTurn;
		robot.setTurnRadarRightRadians(turn);
	}
}
