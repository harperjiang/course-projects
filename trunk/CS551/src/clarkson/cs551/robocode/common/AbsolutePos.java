package clarkson.cs551.robocode.common;

import java.awt.geom.Point2D;
import java.text.MessageFormat;

public class AbsolutePos {

	private long time;

	private Point2D.Double position;

	private Velocity velocity;

	private Point2D.Double myPosition;

	public AbsolutePos(long time, Point2D.Double pos, Velocity velocity) {
		super();
		this.time = time;
		this.position = pos;
		this.velocity = velocity;
		this.myPosition = new Point2D.Double(0, 0);
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

	public Velocity getVelocity() {
		return velocity;
	}

	public void setVelocity(Velocity velocity) {
		this.velocity = velocity;
	}

	public Point2D.Double getMyPosition() {
		return myPosition;
	}

	public void setMyPosition(Point2D.Double myPosition) {
		this.myPosition = myPosition;
	}

	@Override
	public String toString() {
		return MessageFormat.format("({0},{1}),({3},{4}) at {2}", position.x,
				position.y, time, velocity.getDirection(), velocity.getValue());
	}
}
