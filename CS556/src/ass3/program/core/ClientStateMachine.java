package ass3.program.core;

public class ClientStateMachine {

	protected static enum CState {
		INIT, PUBLIC_KEY_RECEIVED, SHARED_KEY_EXCHANGED
	}

	private CState currentState;

	public ClientStateMachine() {
		super();
		currentState = CState.INIT;
	}

	public CState getCurrentState() {
		return currentState;
	}

	public void transit(CState to) {
		// TODO block invalid state transition
		currentState = to;
	}
}
