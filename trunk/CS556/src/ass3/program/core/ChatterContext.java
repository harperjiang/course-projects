package ass3.program.core;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

import utils.StringUtils;

public class ChatterContext {

	public static final class ContextKey implements Serializable {

		/**
		 * 
		 */
		private static final long serialVersionUID = -5371740632367245004L;

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

		public void setA(String a) {
			this.a = a;
		}

		public void setB(String b) {
			this.b = b;
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

	private Map<String, Map<String, Object>> context = new HashMap<String, Map<String, Object>>();

	private static ChatterContext INSTANCE = new ChatterContext();

	public static final ChatterContext getInstance() {
		return INSTANCE;
	}

	public static synchronized void put(String chooser, String key, Object value) {
		Map<String, Object> data = getInstance().context.get(chooser);
		if (data == null) {
			data = new HashMap<String, Object>();
			getInstance().context.put(chooser, data);
		}
		data.put(key, value);

		// TODO This context should be regularly cleared later
	}

	public static synchronized <T> T get(String chooser, String key) {
		Map<String, Object> data = getInstance().context.get(chooser);
		if (data == null) {
			data = new HashMap<String, Object>();
			getInstance().context.put(chooser, data);
		}
		return (T) data.get(key);
	}

	public static synchronized void clear(String chooser) {
		getInstance().context.remove(chooser);
	}

}
