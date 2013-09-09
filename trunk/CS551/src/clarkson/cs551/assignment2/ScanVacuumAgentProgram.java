package clarkson.cs551.assignment2;

import java.util.HashSet;
import java.util.Set;

import aima.core.agent.Action;
import aima.core.agent.Model;
import aima.core.agent.Percept;
import aima.core.agent.impl.DynamicState;
import aima.core.agent.impl.aprog.ModelBasedReflexAgentProgram;
import aima.core.agent.impl.aprog.simplerule.EQUALCondition;
import aima.core.agent.impl.aprog.simplerule.Rule;

public class ScanVacuumAgentProgram extends ModelBasedReflexAgentProgram {

	public static final String ATTR_CUR_STATE = "attrCurrentState";

	private State stateBeforeClean;

	@Override
	protected void init() {
		DynamicState initState = new DynamicState();
		initState.setAttribute(ATTR_CUR_STATE, State.START);
		setState(initState);

		setRules(makeRules());
	}

	@Override
	protected DynamicState updateState(DynamicState state, Action action,
			Percept percept, Model model) {
		EnhancedVacuumEnvironmentPercept evep = (EnhancedVacuumEnvironmentPercept) percept;

		if (evep.isDirty()) {
			stateBeforeClean = (State) state.getAttribute(ATTR_CUR_STATE);
			state.setAttribute(ATTR_CUR_STATE, State.CLEAN);
			return state;
		}
		switch ((State) (state.getAttribute(ATTR_CUR_STATE))) {
		case CLEAN:
			state.setAttribute(ATTR_CUR_STATE, stateBeforeClean);
			break;
		case START:
			state.setAttribute(ATTR_CUR_STATE, State.INIT_TOP);
			break;
		case STOP:
			break;
		case INIT_TOP:
			if (evep.isWall(Direction.NORTH))
				state.setAttribute(ATTR_CUR_STATE, State.INIT_LEFT);
			break;
		case INIT_LEFT:
			if (evep.isWall(Direction.WEST))
				state.setAttribute(ATTR_CUR_STATE, State.SCAN_RIGHT);
			break;
		case SCAN_LEFT:
			if (evep.isWall(Direction.WEST))
				state.setAttribute(ATTR_CUR_STATE, State.SCAN_DOWN_2);
			break;
		case SCAN_RIGHT:
			if (evep.isWall(Direction.EAST))
				state.setAttribute(ATTR_CUR_STATE, State.SCAN_DOWN_1);
			break;
		case SCAN_DOWN_1:
			if (evep.isWall(Direction.SOUTH))
				state.setAttribute(ATTR_CUR_STATE, State.STOP);
			else
				state.setAttribute(ATTR_CUR_STATE, State.SCAN_LEFT);
			break;
		case SCAN_DOWN_2:
			if (evep.isWall(Direction.SOUTH))
				state.setAttribute(ATTR_CUR_STATE, State.STOP);
			else
				state.setAttribute(ATTR_CUR_STATE, State.SCAN_RIGHT);
			break;
		default:
			break;
		}
		return state;
	}

	private Set<Rule> makeRules() {
		Set<Rule> rules = new HashSet<Rule>();
		rules.add(new Rule(new EQUALCondition(ATTR_CUR_STATE, State.INIT_TOP),
				EnhancedVacuumEnvironment.ACTION_UP));
		rules.add(new Rule(new EQUALCondition(ATTR_CUR_STATE, State.INIT_LEFT),
				EnhancedVacuumEnvironment.ACTION_LEFT));
		rules.add(new Rule(new EQUALCondition(ATTR_CUR_STATE, State.SCAN_LEFT),
				EnhancedVacuumEnvironment.ACTION_LEFT));
		rules.add(new Rule(
				new EQUALCondition(ATTR_CUR_STATE, State.SCAN_RIGHT),
				EnhancedVacuumEnvironment.ACTION_RIGHT));
		rules.add(new Rule(
				new EQUALCondition(ATTR_CUR_STATE, State.SCAN_DOWN_1),
				EnhancedVacuumEnvironment.ACTION_DOWN));
		rules.add(new Rule(
				new EQUALCondition(ATTR_CUR_STATE, State.SCAN_DOWN_2),
				EnhancedVacuumEnvironment.ACTION_DOWN));
		rules.add(new Rule(new EQUALCondition(ATTR_CUR_STATE, State.CLEAN),
				EnhancedVacuumEnvironment.ACTION_CLEAN));
		return rules;
	}

	public static enum State {
		START, STOP, INIT_TOP, INIT_LEFT, SCAN_LEFT, SCAN_RIGHT, SCAN_DOWN_1, SCAN_DOWN_2, CLEAN
	}
}
