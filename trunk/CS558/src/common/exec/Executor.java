package common.exec;

import java.util.Map;

import common.model.Model;

public interface Executor {

	public boolean execute(Model model, Map<String, Object> assignment);
}
