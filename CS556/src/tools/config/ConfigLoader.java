package tools.config;

import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

import org.slf4j.LoggerFactory;

public class ConfigLoader {

	private static Map<String, Properties> cache = new HashMap<String, Properties>();

	public synchronized static String load(String config, String key) {
		try {
			if (!cache.containsKey(config)) {
				Properties prop = new Properties();
				prop.load(Thread.currentThread().getContextClassLoader()
						.getResourceAsStream(config + ".properties"));
				cache.put(config, prop);
			}
			Properties prop = cache.get(config);
			return prop.getProperty(key);
		} catch (Exception e) {
			LoggerFactory.getLogger(ConfigLoader.class).warn(
					"Error loading config", e);
			return null;
		}
	}

	public static int loadInt(String config, String key) {
		String result = load(config, key);
		return Integer.valueOf(result);
	}
}
