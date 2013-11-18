package ass3.program.core;

import java.util.EventListener;

public interface ServerListener extends EventListener {

	public void commandReceived(ServerMessageEvent command);
}
