package ass3.program.core;


public class ServerStateMachine {

	protected static enum SState {
		INIT, PUBLIC_KEY_SENT, SHARED_KEY_RECEIVED
	}

	private SState currentState;

	public ServerStateMachine() {
		super();
		currentState = SState.INIT;
	}

	public void transit(SState newstate) {
		switch (newstate) {
		case PUBLIC_KEY_SENT:
			currentState = newstate;
			break;
		case SHARED_KEY_RECEIVED:
			if (currentState != SState.PUBLIC_KEY_SENT) {
				throw new IllegalStateException();
			}
			currentState = newstate;
			break;
		default:
			throw new IllegalStateException();
		}
	}
}
