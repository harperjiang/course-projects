package ass3.program.core;

public class ClientStateMachine {

	protected static enum State {
		INIT, PUBLIC_KEY_RECEIVED, SHARED_KEY_EXCHANGED
	}

	private State currentState;

	public ClientStateMachine() {
		super();
		currentState = State.INIT;
	}

	public State getCurrentState() {
		return currentState;
	}

	public void transit(State to) {
		// TODO block invalid state transition
		currentState = to;
	}
}
