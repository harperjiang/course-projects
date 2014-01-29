package common.model;

public enum Operator {

	AND("and"), OR("or"), NOT("not"), EQUAL("="), IMPLY("=>"), GE(
			">="), LE("<="), GT(">"), LT("<"), ADD("+"), SUB("-");

	String value;

	Operator(String value) {
		this.value = value;
	}

	public String getValue() {
		return value;
	}
}
