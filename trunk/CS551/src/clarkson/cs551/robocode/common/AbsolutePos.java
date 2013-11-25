package clarkson.cs551.robocode.common;

import java.awt.geom.Point2D;
import java.text.MessageFormat;

public class AbsolutePos {

	private long time;

	private Point2D.Double position;

	public AbsolutePos(long time, Point2D.Double pos) {
		super();
		this.time = time;
		this.position = pos;
	}

	public double getX() {
		return position.getX();
	}

	public double getY() {
		return position.getY();
	}

	public long getTime() {
		return time;
	}

	public void setTime(long time) {
		this.time = time;
	}

	public Point2D.Double getPosition() {
		return position;
	}

	public void setPosition(Point2D.Double position) {
		this.position = position;
	}

	@Override
	public String toString() {
		return MessageFormat.format("({0},{1}) at {2}", position.x, position.y,
				time);
	}
}
