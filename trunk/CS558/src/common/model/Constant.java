package common.model;

public class Constant extends Predicate {

	private Object value;

	public Constant(Object value) {
		super();
		this.value = value;
	}

	@Override
	public String toString() {
		return value.toString();
	}
}
