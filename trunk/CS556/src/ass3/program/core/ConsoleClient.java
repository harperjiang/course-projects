package ass3.program.core;

public class ConsoleClient {

	public static void main(String[] args) {
		Chatter chatter = new Chatter();
		chatter.send("128.153.177.239", "Hello?");
	}
}
