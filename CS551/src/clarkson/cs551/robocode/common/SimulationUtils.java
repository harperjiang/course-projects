package clarkson.cs551.robocode.common;

public class SimulationUtils {

	public static double distance(int round) {
		if (round >= 12)
			return 8 * (round - 12) + 48;
		int decRound = (int) Math.floor(round / 3);
		int incRound = decRound * 2;
		int remain = round - incRound - decRound;
		switch (remain) {
		case 0:
			return incRound * (1 + incRound) / 2 + decRound * (1 + decRound);
		case 1:
			return incRound * (1 + incRound) / 2 + decRound * (1 + decRound)
					+ incRound;
		case 2:
			return (incRound + 1) * (2 + incRound) / 2 + decRound
					* (1 + decRound);
		default:
			return 0;
		}
	}

	/**
	 * Robot speed simulation
	 */
	public static double simulate(double remain, double speed) {
		if (remain == 0)
			return 0;
		// From current speed, what distance will need to decrease to zero?
		if (remain - (speed + 1) >= min(speed + 1)) {
			// Full speed increase
			return Math.min(8, speed + 1);
		}
		if ((remain - speed) >= min(speed)
				&& remain - (speed + 1) < min(speed + 1)) {
			double x = 0;
			// A little increase
			double round = Math.ceil(speed / 2);
			if (round == speed / 2) {
				// one more round
				x = (remain - speed - min(speed)) / round;
			} else {
				x = (remain - speed - min(speed)) / (round - 1);
			}
			return speed + x;
		}
		if (remain - speed < min(speed)) {
			// Decrease
			double round = Math.ceil(speed / 2);
			double x = 0;
			if (round == speed / 2) {
				x = (remain - min(speed)) / (round);
			} else {
				x = (remain - min(speed)) / (round - 1);
			}
			return Math.max(0, speed - (2 - x));
		}
		System.out.println("Error");
		return -1;
	}

	protected static double min(double speed) {
		double round = Math.ceil(speed / 2) - 1;
		double min = round * speed - round * (1 + round);
		return min;
	}
}
