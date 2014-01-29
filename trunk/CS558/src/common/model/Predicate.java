package common.model;

public class Predicate {

	private Operator opr;

	private Predicate[] children;

	public Predicate() {
		super();
	}

	public Predicate(Operator opr, Predicate... children) {
		this();
		this.opr = opr;
		this.children = children;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();

		sb.append("(").append(opr.getValue()).append(" ");
		for (Predicate child : children) {
			sb.append(child).append(" ");
		}
		sb.append(")");
		return sb.toString();
	}
}
