package ass1.project.gui;

import java.awt.Dimension;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class LabeledFileChooser extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = -2043161819048934807L;

	private JLabel label;

	private JTextField textField;

	private FileButton button;

	public LabeledFileChooser(String label) {
		super();
		this.label = new JLabel(label);
		this.label.setPreferredSize(new Dimension(150, 25));
		add(this.label);
		this.textField = new JTextField();
		this.textField.setEditable(false);
		this.textField.setPreferredSize(new Dimension(175, 25));
		add(this.textField);
		this.button = new FileButton(textField);
		add(this.button);
	}

	public JLabel getLabel() {
		return label;
	}

	public JTextField getTextField() {
		return textField;
	}

	public FileButton getButton() {
		return button;
	}

}
