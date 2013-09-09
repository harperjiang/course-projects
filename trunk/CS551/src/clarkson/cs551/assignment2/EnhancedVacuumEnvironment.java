package clarkson.cs551.assignment2;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import aima.core.agent.Action;
import aima.core.agent.Agent;
import aima.core.agent.EnvironmentState;
import aima.core.agent.Percept;
import aima.core.agent.impl.AbstractEnvironment;
import aima.core.agent.impl.DynamicAction;

public class EnhancedVacuumEnvironment extends AbstractEnvironment {

	public static final Action ACTION_UP = new DynamicAction("Up");
	public static final Action ACTION_DOWN = new DynamicAction("Down");
	public static final Action ACTION_LEFT = new DynamicAction("Left");
	public static final Action ACTION_RIGHT = new DynamicAction("Right");
	public static final Action ACTION_CLEAN = new DynamicAction("Clean");

	private EnhancedVacuumEnvironmentState state;

	private Map<Agent, Location> agentLocations;

	public EnhancedVacuumEnvironment() {
		this(20, 20);
	}

	public EnhancedVacuumEnvironment(int width, int height) {
		super();

		state = new EnhancedVacuumEnvironmentState();
		agentLocations = new HashMap<Agent, Location>();

		// Init the state
		initRandomState(width, height);
	}

	private void initRandomState(int width, int height) {
		// Init the state
		state.tiles = new int[width][height];
		for (int i = 0; i < width * height - 1; i++) {
			// Initialize clean carpet
			state.tiles[i / height][i % height] = 0;
		}
		// Randomly generate 1/20 dirty tiles
		Random rand = new Random(System.currentTimeMillis());
		int dirty = rand.nextInt((int) (width * height / 20));
		for (int i = 0; i < dirty; i++) {
			int x = -1, y = -1;
			while (!(x >= 0 && y >= 0 && state.tiles[x][y] != 2)) {
				x = rand.nextInt(state.width);
				y = rand.nextInt(state.height);
			}
			state.tiles[x][y] = 1;
		}
	}

	@Override
	public EnvironmentState getCurrentState() {
		return state;
	}

	@Override
	public void addAgent(Agent a) {
		super.addAgent(a);
		// Randomly init the agent location
		Random rand = new Random(System.currentTimeMillis());
		int x = -1, y = -1;
		while (!(x >= 0 && y >= 0 && state.tiles[x][y] != 2)) {
			x = rand.nextInt(state.width);
			y = rand.nextInt(state.height);
		}
		agentLocations.put(a, new Location(x, y));
	}

	@Override
	public EnvironmentState executeAction(Agent agent, Action action) {
		Location currentLoc = agentLocations.get(agent);
		if (null == currentLoc)
			return null;
		if (ACTION_UP == action) {
			currentLoc.setY(currentLoc.getY() - 1);
		}
		if (ACTION_DOWN == action) {
			currentLoc.setY(currentLoc.getY() + 1);
		}
		if (ACTION_LEFT == action) {
			currentLoc.setX(currentLoc.getX() - 1);
		}
		if (ACTION_RIGHT == action) {
			currentLoc.setX(currentLoc.getX() + 1);
		}
		if (ACTION_CLEAN == action) {
			state.tiles[currentLoc.getX()][currentLoc.getY()] = 0;
		}
		return state;
	}

	@Override
	public Percept getPerceptSeenBy(Agent anAgent) {
		Location loc = agentLocations.get(anAgent);
		if (null == loc)
			return null;
		return new EnhancedVacuumEnvironmentPercept(
				loc.getY() == 0 || state.tiles[loc.getX()][loc.getY() - 1] == 2,
				loc.getX() == 0 || state.tiles[loc.getX() - 1][loc.getY()] == 2,
				loc.getY() == state.height - 1
						|| state.tiles[loc.getX()][loc.getY() + 1] == 2, loc
						.getX() == state.width - 1
						|| state.tiles[loc.getX() + 1][loc.getY()] == 2,
				state.tiles[loc.getX()][loc.getY()] == 1);
	}

	// 2D array to store the environment information.
	// 0 means clean carpet, 1 means dirty carpet, 2 means wall,
	// array boundary means wall
	public static class EnhancedVacuumEnvironmentState implements
			EnvironmentState {
		protected int width;
		protected int height;
		protected int[][] tiles;
	}
}
