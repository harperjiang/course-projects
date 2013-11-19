package ass3.program.core;

public class ConsoleClient {

	public static void main(String[] args) {
		Chatter chatter = new Chatter();
		chatter.send("10.0.2.2", "Hello?");
	}
}
