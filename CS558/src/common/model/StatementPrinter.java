package common.model;

import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.List;

public class StatementPrinter {

	public static void print(List<Statement> input, OutputStream os) {
		PrintWriter pw = new PrintWriter(os);
		for (Statement st : input) {
			pw.println(st);
		}
		pw.flush();
	}
}
