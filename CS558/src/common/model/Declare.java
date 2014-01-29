package common.model;

import java.text.MessageFormat;

public class Declare extends Statement {

	private String name;

	private Type type;

	public Declare(String name, Type type) {
		this.name = name;
		this.type = type;
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();

		sb.append(MessageFormat.format("(declare-var {0} {1})", name,
				type.name()));

		return sb.toString();
	}
}
