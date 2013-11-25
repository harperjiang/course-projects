package clarkson.cs551.robocode.moving;

import java.awt.geom.Point2D;

public interface Coordinate {

	public Point2D getMyPosition();

	public void move(double direction, double distance);
}
