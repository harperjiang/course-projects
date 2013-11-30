package clarkson.cs551.robocode.moving;

import java.awt.geom.Point2D;
import java.util.Stack;

import robocode.util.Utils;
import clarkson.cs551.BasicRobot;
import clarkson.cs551.robocode.common.GeometricUtils;

public abstract class AbstractMovingHandler implements MovingHandler {

	private Stack<Operation> operations;

	private boolean interrupt = false;

	public AbstractMovingHandler() {
		super();
		operations = new Stack<Operation>();
	}

	protected void triggerInterrupt() {
		interrupt = true;
	}

	@Override
	public void action(BasicRobot robot) {
		if (operations.isEmpty()) {
			Point2D.Double nextpos = estimate(robot);
			if (null == nextpos)
				return;
			double distance = GeometricUtils.getDistance(robot.getPosition(),
					nextpos);
			double angle = Utils.normalRelativeAngle(GeometricUtils.getRadian(
					robot.getPosition(), nextpos)
					- GeometricUtils.absoluteHeading(robot.getHeading()));
			operations.push(new MoveOperation(distance,
					Math.abs(angle) > Math.PI / 2));
			operations.push(new RotateOperation(angle));
			action(robot);
		} else if (interrupt) {
			operations.clear();
			interrupt = false;
			action(robot);
		} else {
			// Execute operation
			while (true) {
				if (operations.isEmpty())
					break;
				Operation opr = operations.peek();
				if (!opr.submitted()) {
					System.out.println("Executing Operation:"
							+ opr.getClass().getSimpleName());
					opr.execute(robot);
				}
				if (opr.done()) {
					operations.pop();
				} else {
					break;
				}
			}
		}
	}

	protected abstract Point2D.Double estimate(BasicRobot robot);

	@Override
	public void initialize(BasicRobot robot) {
		loadData(robot);
	}

	@Override
	public void loadData(BasicRobot robot) {
	}

	@Override
	public void storeData(BasicRobot robot) {
	}

}
