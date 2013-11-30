package clarkson.cs551.robocode.moving;

import java.awt.geom.Point2D;

public class EnemyStatus {

	private double energy;

	private double energyChange;

	private double heading;

	private Point2D.Double position;

	private double distance;

	private double velocity;

	public double getEnergy() {
		return energy;
	}

	public void setEnergy(double energy) {
		this.energy = energy;
	}

	public double getEnergyChange() {
		return energyChange;
	}

	public void setEnergyChange(double energyChange) {
		this.energyChange = energyChange;
	}

	public double getHeading() {
		return heading;
	}

	public void setHeading(double heading) {
		this.heading = heading;
	}

	public Point2D.Double getPosition() {
		return position;
	}

	public void setPosition(Point2D.Double position) {
		this.position = position;
	}

	public double getVelocity() {
		return velocity;
	}

	public void setVelocity(double velocity) {
		this.velocity = velocity;
	}

	public double getDistance() {
		return distance;
	}

	public void setDistance(double distance) {
		this.distance = distance;
	}

}
