package ass3.program.core;

import ass3.program.core.message.ExchSharedKeyRequest;
import ass3.program.core.message.PublicKeyRequest;
import ass3.program.core.message.Request;
import ass3.program.core.message.SendTextRequest;

public class ServerStateMachine {

	protected static enum State {
		INIT, PUBLIC_KEY_SENT, SHARED_KEY_RECEIVED
	}

	private State currentState;

	public ServerStateMachine() {
		super();
		currentState = State.INIT;
	}

	public boolean transit(Request request) {
		if (request instanceof PublicKeyRequest) {// Always support starting a
													// new negoation
			currentState = State.PUBLIC_KEY_SENT;
			return true;
		}
		if (request instanceof ExchSharedKeyRequest
				&& currentState == State.PUBLIC_KEY_SENT) {
			currentState = State.SHARED_KEY_RECEIVED;
			return true;
		}
		if (request instanceof SendTextRequest
				&& currentState == State.SHARED_KEY_RECEIVED) {
			return true;
		}
		return false;
	}
}
