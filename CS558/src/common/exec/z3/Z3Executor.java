package common.exec.z3;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.text.MessageFormat;
import java.util.List;
import java.util.Map;

import java_cup.runtime.Symbol;

import common.exec.Assign;
import common.exec.AssignResult;
import common.exec.Executor;
import common.exec.Result;
import common.exec.SatResult;
import common.model.Model;
import common.model.Statement;
import common.model.StatementPrinter;

public class Z3Executor implements Executor {

	private static final String FOLDER = "/home/harper/Libraries/z3-4.3.2.a5335270042c-x64-ubuntu-12.04";

	@Override
	public boolean execute(Model model, Map<String, Object> assignment) {
		try {
			List<Statement> statements = model.generate();
			
			String exe = MessageFormat.format("{0}{1}bin{1}{2}", FOLDER,
					File.separator, "z3");

			ProcessBuilder builder = new ProcessBuilder(exe, "-smt2", "-in");
			builder.redirectErrorStream(true);
			Process process = builder.start();


			StatementPrinter.print(statements, process.getOutputStream());
			process.getOutputStream().flush();
			process.getOutputStream().close();
			process.waitFor();

			Parser parser = new Parser(new Lexer(process.getInputStream()));
			List<Result> parsed = (List<Result>) parser.parse().value;

			boolean result = false;
			for (Result res : parsed) {
				if (res instanceof SatResult) {
					SatResult sat = (SatResult) res;
					result = sat.isSat();
				}
				if (res instanceof AssignResult) {
					AssignResult assr = (AssignResult) res;
					for (Assign assign : assr.getAssigns()) {
						assignment.put(assign.getVar(), assign.getValue());
					}
				}
			}
			return result;
		} catch (Exception e) {
			if (e instanceof RuntimeException)
				throw (RuntimeException) e;
			throw new RuntimeException(e);
		}
	}

	private void outputContent(InputStream output) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(output));
		String line = null;
		while (null != (line = br.readLine())) {
			System.out.println(line);
		}
	}

	private void outputSymbol(InputStream input) throws IOException {
		Lexer lexer = new Lexer(input);
		Symbol sym = null;
		while ((sym = lexer.next_token()).sym != Syms.EOF) {
			System.out.println(sym.sym);
		}
	}
}
