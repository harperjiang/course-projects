package clarkson.cs551.robocode.common;

import java.awt.geom.Point2D;

import robocode.util.Utils;

public class GeometricUtils {

	public static double getDistance(Point2D.Double p1) {
		return Math.sqrt(Math.pow(p1.getX(), 2) + Math.pow(p1.getY(), 2));
	}

	public static double getDistance(Point2D.Double p1, Point2D.Double p2) {
		return Math.sqrt(Math.pow(p1.getX() - p2.getX(), 2)
				+ Math.pow(p1.getY() - p2.getY(), 2));
	}

	public static double getSlope(Point2D.Double start, Point2D.Double end) {
		return (end.getX() == start.getX()) ? Double.NaN : (end.getY() - start
				.getY()) / (end.getX() - start.getX());
	}

	public static double getRadian(Point2D.Double origin, Point2D.Double target) {
		double x = target.getX() - origin.getX();
		double y = target.getY() - origin.getY();
		double dist = Math.sqrt(Math.pow(y, 2) + Math.pow(x, 2));
		double asin = Math.asin(y / dist);
		if (x < 0) {
			asin = Math.PI - asin;
		}
		return Utils.normalAbsoluteAngle(asin);
	}

	public static double getRadian(Point2D.Double point) {
		double dist = Math.sqrt(Math.pow(point.y, 2) + Math.pow(point.x, 2));
		double asin = Math.asin(point.y / dist);
		if (point.x < 0) {
			asin = Math.PI - asin;
		}
		return Utils.normalAbsoluteAngle(asin);
	}

	public static double absoluteHeading(double robotHeading) {
		return Utils.normalAbsoluteAngle(Math.PI / 2 - robotHeading);
	}
}
