package clarkson.cs551.robocode.targeting;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import robocode.Bullet;
import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
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
