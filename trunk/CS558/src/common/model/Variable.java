package common.model;

public class Variable extends Predicate {

	private String var;

	public Variable(String var) {
		super();
		this.var = var;
	}

	@Override
	public String toString() {
		return this.var;
	}
}
