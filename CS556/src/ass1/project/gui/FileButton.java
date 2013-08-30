package ass1.project.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JTextField;

public class FileButton extends JButton {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1013281914095611584L;

	private File selectedFile;

	private JTextField text;

	public FileButton(JTextField text) {
		super("...");
		this.text = text;
		addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				JFileChooser fileChooser = new JFileChooser();
				fileChooser.showDialog(FileButton.this, "Select");
				if (null != fileChooser.getSelectedFile()) {
					FileButton.this.selectedFile = fileChooser
							.getSelectedFile();
					FileButton.this.text
							.setText(selectedFile.getAbsolutePath());
				}
			}
		});
	}

	public File getSelectedFile() {
		return selectedFile;
	}
}
