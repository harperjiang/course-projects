package ass3.program.core;

import java.util.HashMap;
import java.util.Map;

import utils.StringUtils;

public class ChatterContext {

	public static final class ContextKey {

		private String a;

		private String b;

		public ContextKey(String a, String b) {
			this.a = a;
			this.b = b;
			if (StringUtils.isEmpty(a) || StringUtils.isEmpty(b)) {
				throw new IllegalArgumentException();
			}
		}

		public String getA() {
			return a;
		}

		public String getB() {
			return b;
		}

		@Override
		public boolean equals(Object obj) {
			if (!(obj instanceof ContextKey))
				return super.equals(obj);
			ContextKey another = (ContextKey) obj;
			return (a.equals(another.a) && b.equals(another.b))
					|| (a.equals(another.b) && b.equals(another.a));
		}

		@Override
		public int hashCode() {
			return a.hashCode() + b.hashCode();
		}
	}

	private ChatterContext() {

	}

	private Map<ContextKey, Map<String, Object>> context = new HashMap<ContextKey, Map<String, Object>>();

	private static ChatterContext INSTANCE = new ChatterContext();

	public static final ChatterContext getInstance() {
		return INSTANCE;
	}

	public static synchronized void put(ContextKey ck, String key, Object value) {
		Map<String, Object> data = getInstance().context.get(ck);
		if (data == null) {
			data = new HashMap<String, Object>();
			getInstance().context.put(ck, data);
		}
		data.put(key, value);

		// TODO This context should be regularly cleared later
	}

	public static synchronized <T> T get(ContextKey ck, String key) {
		Map<String, Object> data = getInstance().context.get(ck);
		if (data == null) {
			data = new HashMap<String, Object>();
			getInstance().context.put(ck, data);
		}
		return (T) data.get(key);
	}

	public static synchronized void clear(ContextKey ck) {
		getInstance().context.remove(ck);
	}

}
