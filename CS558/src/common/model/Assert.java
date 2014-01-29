package common.model;

import java.text.MessageFormat;

public class Assert extends Statement {

	private Predicate predict;

	public Assert(Predicate predict) {
		this.predict = predict;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(MessageFormat.format("(assert {0})", predict));
		return sb.toString();
	}
}
