package clarkson.cs551.robocode.targeting;

import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.List;

public class AccuracySta {

	private int pending;

	private List<DistanceData> data;

	public AccuracySta() {
		data = new ArrayList<DistanceData>();
	}

	public void fired(int distance) {
		pending = distance;
	}

	public void hit() {
		process(pending, true);
	}

	public void missed() {
		process(pending, false);
	}

	protected void process(int distance, boolean hit) {
		while (data.size() <= distance) {
			data.add(new DistanceData());
		}
		if (hit)
			data.get(distance).hit();
		else
			data.get(distance).missed();
	}

	public double accuracy(int distance) {
		if (data.size() <= distance)
			return 0;
		return data.get(distance).accuracy();
	}

	public static final class DistanceData {
		int count = 0;
		int hit = 0;

		public void hit() {
			count++;
			hit++;
		}

		public void missed() {
			count++;
		}

		public double accuracy() {
			if (0 == count)
				return 0;
			return ((double) hit) / ((double) count);
		}
	}

	public void report() {
		for (int i = 0; i < data.size(); i++) {
			System.out.println(MessageFormat.format("{0}:{1}", i, data.get(i)
					.accuracy()));
		}
	}

}
