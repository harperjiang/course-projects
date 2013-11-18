package ass3.program.core;

import ass3.program.core.message.Request;

public class ServerStateMachine {

	protected static enum State {
		INIT, KEY_REQUESTED,
	}

	private State currentState;

	public ServerStateMachine() {
		super();
		currentState = State.INIT;
	}

	public void transit(Request cmd) {
		// TODO Auto-generated method stub

	}

}
