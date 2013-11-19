package ass3.program.core;

import java.util.HashMap;
import java.util.Map;

public class ChatterContext {

	private ChatterContext() {

	}

	private ThreadLocal<Map<String, Object>> context = new ThreadLocal<Map<String, Object>>() {
		@Override
		protected Map<String, Object> initialValue() {
			return new HashMap<String, Object>();
		}
	};

	private static ChatterContext INSTANCE = new ChatterContext();

	public static final ChatterContext getInstance() {
		return INSTANCE;
	}

	public static void put(String key, Object value) {
		getInstance().context.get().put(key, value);
	}

	public static <T> T get(String key) {
		return (T) getInstance().context.get().get(key);
	}

}
