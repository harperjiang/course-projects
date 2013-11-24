package clarkson.cs551.robocode.common;

public class RelativePos {

	private double direction;

	private double distance;

	public RelativePos(double dir, double dist) {
		this.direction = dir;
		this.distance = dist;
	}

	public double getDirection() {
		return direction;
	}

	public void setDirection(double direction) {
		this.direction = direction;
	}

	public double getDistance() {
		return distance;
	}

	public void setDistance(double distance) {
		this.distance = distance;
	}

}
