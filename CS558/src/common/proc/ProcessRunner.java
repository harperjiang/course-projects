package common.proc;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class ProcessRunner {

	private String[] commands;

	private OutputHandler handler;

	private File currentDir;

	private transient Process process;

	public ProcessRunner(String... commands) {
		this.commands = commands;
	}

	/**
	 * Wait until the process ends
	 * 
	 * @throws InterruptedException
	 */
	public int runAndWait() throws InterruptedException, IOException {
		ProcessBuilder builder = new ProcessBuilder(commands);
		builder.redirectErrorStream(true);
		if (null != currentDir) {
			builder.directory(currentDir);
		}

		process = builder.start();
		int result = process.waitFor();
		if (null != handler) {
			BufferedReader br = new BufferedReader(new InputStreamReader(
					process.getInputStream()));
			String line = null;
			while (null != (line = br.readLine())) {
				handler.output(line);
			}
		}
		return result;
	}
	
	public void interact() throws InterruptedException, IOException {
		
	}

	public void runLater(final Callback callback) {
		new Thread() {
			public void run() {
				try {
					ProcessRunner.this.runAndWait();
					callback.done();
				} catch (Exception e) {
					callback.exception(e);
				} finally {
					callback.clean();
				}
			}
		}.start();
	}

	public Process getProcess() {
		return process;
	}

	public OutputHandler getHandler() {
		return handler;
	}

	public void setHandler(OutputHandler handler) {
		this.handler = handler;
	}

	public File getCurrentDir() {
		return currentDir;
	}

	public void setCurrentDir(File currentDir) {
		this.currentDir = currentDir;
	}

	public static interface Callback {
		public void done();

		public void exception(Exception e);

		public void clean();
	}
}
