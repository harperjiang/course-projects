package common.model;

public class Check extends Statement {
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("(check-sat)").append("\n");
		sb.append("(get-model)").append("\n");
		return sb.toString();
	}
}
