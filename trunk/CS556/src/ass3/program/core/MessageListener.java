package ass3.program.core;

import java.util.EventListener;

public interface MessageListener extends EventListener {

	public void messageReceived(MessageEvent event);

}
