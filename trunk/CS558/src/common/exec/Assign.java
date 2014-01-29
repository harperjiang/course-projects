package common.exec;

public class Assign {

	private String var;

	private Object value;

	public Assign(String var, Object value) {
		this.var = var;
		this.value = value;
	}

	public Object getValue() {
		return value;
	}

	public void setValue(Object value) {
		this.value = value;
	}

	public String getVar() {
		return var;
	}

	public void setVar(String var) {
		this.var = var;
	}

}
