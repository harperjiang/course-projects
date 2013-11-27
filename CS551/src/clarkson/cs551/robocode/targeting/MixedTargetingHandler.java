package clarkson.cs551.robocode.targeting;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import robocode.AdvancedRobot;
import robocode.Bullet;
import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.ScannedRobotEvent;
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
	protected FireResult estimate(AdvancedRobot robot) {
		// Randomly choose a Handler to handle
		lastChoice = RandomUtils.randomChoose(weights);
		return handlers.get(lastChoice).estimate(robot);
	}

	@Override
	protected void onNewPath(AbsolutePos path) {
		for (AbstractTargetingHandler handler : handlers)
			handler.onNewPath(path);
	}

	@Override
	public void enemyScanned(AdvancedRobot self, ScannedRobotEvent event) {
		for (AbstractTargetingHandler handler : handlers)
			handler.enemyScanned(self, event);
	}

	@Override
	public void bulletFired(Bullet bullet) {
		history.put(bullet, lastChoice);
	}

	@Override
	public void bulletHit(AdvancedRobot self, BulletHitEvent event) {
		// Do nothing
		history.remove(event.getBullet());
	}

	@Override
	public void bulletHitBullet(AdvancedRobot robot, BulletHitBulletEvent event) {
		// Do nothing
		history.remove(event.getBullet());
	}

	@Override
	public void bulletMissed(AdvancedRobot self, BulletMissedEvent event) {
		int index = history.remove(event.getBullet());
		weights.set(index, weights.get(index) / 2);
	}
}
