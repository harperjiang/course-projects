package clarkson.cs551;

import java.awt.geom.Point2D;
import java.awt.geom.Point2D.Double;

import robocode.AdvancedRobot;
import robocode.StatusEvent;

public abstract class BasicRobot extends AdvancedRobot {

	private Point2D.Double position;

	public BasicRobot() {
		super();
		position = new Point2D.Double(0, 0);
	}

	@Override
	public void onStatus(StatusEvent e) {
		super.onStatus(e);
		position.x = e.getStatus().getX();
		position.y = getBattleFieldHeight() - e.getStatus().getY();
	}

	public Double getPosition() {
		return position;
	}
}
