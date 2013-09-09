package clarkson.cs551.assignment2;

import aima.core.agent.Percept;

public class EnhancedVacuumEnvironmentPercept implements Percept {

	private boolean topwall;
	private boolean leftwall;
	private boolean bottomwall;
	private boolean rightwall;
	private boolean dirty;

	public EnhancedVacuumEnvironmentPercept(boolean topwall, boolean leftwall,
			boolean bottomwall, boolean rightwall, boolean dirty) {
		this.topwall = topwall;
		this.bottomwall = bottomwall;
		this.leftwall = leftwall;
		this.rightwall = rightwall;
		this.dirty = dirty;
	}

	public boolean isWall(Direction dir) {
		switch (dir) {
		case NORTH:
			return topwall;
		case SOUTH:
			return bottomwall;
		case WEST:
			return leftwall;
		case EAST:
			return rightwall;
		default:
			return false;
		}
	}

	public boolean isDirty() {
		return dirty;
	}
}
