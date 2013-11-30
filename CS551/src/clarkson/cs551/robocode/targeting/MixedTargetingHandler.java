package clarkson.cs551.robocode.targeting;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import robocode.Bullet;
import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.RobocodeFileOutputStream;
import robocode.ScannedRobotEvent;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.common.AbsolutePos;
import clarkson.cs551.robocode.common.RandomUtils;

public class MixedTargetingHandler extends AbstractTargetingHandler {

	private List<AbstractTargetingHandler> handlers;

	private Map<Bullet, Integer> history;

	private List<Double> weights;

	private int lastChoice;

	public MixedTargetingHandler() {
		super(30);
		handlers = new ArrayList<AbstractTargetingHandler>();
		weights = new ArrayList<Double>();

		handlers.add(new LinearHandler());
		handlers.add(new CircularHandler());
		handlers.add(new GuessFactorHandler());

		weights.add(1d);
		weights.add(1d);
		weights.add(1d);

		history = new HashMap<Bullet, Integer>();
	}

	protected static final String DATA_FILE = "MixedTarget";

	@Override
	public void loadData(BasicRobot robot) {
		super.loadData(robot);
		File dataFile = robot.getDataFile(DATA_FILE);
		if (dataFile.isFile()) {
			try {
				BufferedReader br = new BufferedReader(new InputStreamReader(
						new FileInputStream(dataFile)));
				weights.clear();
				for (int i = 0; i < handlers.size(); i++) {
					String line = br.readLine();
					if (line != null) {
						weights.add(new BigDecimal(line).doubleValue());
					} else {
						weights.add(1d);
					}
				}
				br.close();
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		}
	}

	@Override
	public void storeData(BasicRobot robot) {
		super.storeData(robot);
		// Adjust the weight
		double min = Double.MAX_VALUE;
		for (int i = 0; i < weights.size(); i++) {
			if (min > weights.get(i))
				min = weights.get(i);
		}
		if (min <= 0.01d)
			for (int i = 0; i < weights.size(); i++) {
				weights.set(i, weights.get(i) * 100);
			}

		File dataFile = robot.getDataFile(DATA_FILE);
		try {
			PrintWriter pw = new PrintWriter(new RobocodeFileOutputStream(
					dataFile));
			for (int i = 0; i < weights.size(); i++) {
				pw.println(new BigDecimal(weights.get(i)).toPlainString());
			}
			pw.close();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	@Override
	public void clearBattleData(BasicRobot robot) {
		super.clearBattleData(robot);
		robot.getDataFile(DATA_FILE).delete();
	}

	@Override
	protected FireResult estimate(BasicRobot robot) {
		// Randomly choose a Handler to handle
		lastChoice = RandomUtils.randomChoose(weights);
		return handlers.get(lastChoice).estimate(robot);
	}

	@Override
	protected void onNewPath(AbsolutePos path) {
		super.onNewPath(path);
		for (AbstractTargetingHandler handler : handlers)
			handler.onNewPath(path);
	}

	@Override
	public void enemyScanned(BasicRobot self, ScannedRobotEvent event) {
		super.enemyScanned(self, event);
		for (AbstractTargetingHandler handler : handlers)
			handler.enemyScanned(self, event);
	}

	@Override
	public void bulletFired(BasicRobot robot, Bullet bullet) {
		super.bulletFired(robot, bullet);
		history.put(bullet, lastChoice);
	}

	@Override
	public void bulletHit(BasicRobot self, BulletHitEvent event) {
		super.bulletHit(self, event);
		history.remove(event.getBullet());
	}

	@Override
	public void bulletHitBullet(BasicRobot robot, BulletHitBulletEvent event) {
		super.bulletHitBullet(robot, event);
		history.remove(event.getBullet());
	}

	@Override
	public void bulletMissed(BasicRobot self, BulletMissedEvent event) {
		super.bulletMissed(self, event);
		int index = history.remove(event.getBullet());
		weights.set(index, weights.get(index) / 2);
	}
}
