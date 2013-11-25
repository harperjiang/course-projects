package clarkson.cs551.robocode.common;

public class Velocity {

	private double direction;

	private double value;

	public Velocity(double dir, double val) {
		this.direction = dir;
		this.value = val;
	}

	public double getDirection() {
		return direction;
	}

	public void setDirection(double direction) {
		this.direction = direction;
	}

	public double getValue() {
		return value;
	}

	public void setValue(double value) {
		this.value = value;
	}

	public double getVx() {
		return Math.cos(direction) * value;
	}

	public double getVy() {
		return Math.sin(direction) * value;
	}

}
