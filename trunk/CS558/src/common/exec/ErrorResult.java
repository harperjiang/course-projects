package common.exec;

public class ErrorResult extends Result {

	private String content;

	public ErrorResult(String content) {
		this.content = content;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

}
