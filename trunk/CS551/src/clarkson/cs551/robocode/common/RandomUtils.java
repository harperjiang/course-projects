package clarkson.cs551.robocode.common;

import java.util.List;
import java.util.Random;

public class RandomUtils {

	public static int randomChoose(List<Double> weights) {
		Random random = new Random(System.currentTimeMillis());

		Double sum = 0d;
		for (double weight : weights)
			sum += weight;
		double c = random.nextDouble() * sum;
		double now = 0;
		for (int i = 0; i < weights.size(); i++) {
			now += weights.get(i);
			if (now >= c)
				return i;
		}
		return weights.size() - 1;
	}

}
