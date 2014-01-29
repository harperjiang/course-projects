package common.exec;

import java.util.List;

public class AssignResult extends Result {

	private List<Assign> assigns;

	public AssignResult(List<Assign> assigns) {
		super();
		this.assigns = assigns;
	}

	public List<Assign> getAssigns() {
		return assigns;
	}
}
