package common.exec;

public class SatResult extends Result {

	private boolean sat;

	public SatResult(boolean sat) {
		this.sat = sat;
	}

	public boolean isSat() {
		return sat;
	}

	public void setSat(boolean sat) {
		this.sat = sat;
	}

}
