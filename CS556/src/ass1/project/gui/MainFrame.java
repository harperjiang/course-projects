package ass1.project.gui;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;

import ass1.project.core.Ass1Cipher;

public class MainFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4864081143012686276L;

	private LabeledFileChooser inputChooser;

	private LabeledFileChooser outputChooser;

	private JButton startButton;

	public MainFrame() {
		super();

		setTitle("Assignment 1 for CS556");
		setSize(400, 200);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

		setLayout(new FlowLayout());

		inputChooser = new LabeledFileChooser("Choose Input File");
		add(inputChooser);

		outputChooser = new LabeledFileChooser("Choose Output File");
		add(outputChooser);

		startButton = new JButton("Start");
		startButton.setPreferredSize(new Dimension(100, 30));
		startButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				
			}
		});
		add(startButton);

		doLayout();
		setVisible(true);
	}

	public static void main(String[] args) {
		new MainFrame();
	}
}
