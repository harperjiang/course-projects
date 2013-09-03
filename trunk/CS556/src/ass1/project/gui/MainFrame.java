package ass1.project.gui;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

import utils.IOUtils;
import utils.StringUtils;
import ass1.project.core.Ass1Cipher;
import ass1.project.io.DecryptionInputStream;
import ass1.project.io.EncryptionInputStream;

public class MainFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4864081143012686276L;

	private LabeledFileChooser inputChooser;

	private LabeledFileChooser outputChooser;

	private JRadioButton encryptButton;

	private JRadioButton decryptButton;

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

		encryptButton = new JRadioButton("Encrypt");
		decryptButton = new JRadioButton("Decrypt");
		ButtonGroup bg = new ButtonGroup();
		bg.add(encryptButton);
		bg.add(decryptButton);

		JPanel panel = new JPanel();
		panel.setPreferredSize(new Dimension(375, 25));
		panel.add(encryptButton);
		panel.add(decryptButton);
		encryptButton.setSelected(true);
		add(panel);

		startButton = new JButton("Start");
		startButton.setPreferredSize(new Dimension(100, 30));
		startButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (StringUtils.isEmpty(inputChooser.getTextField().getText())
						|| StringUtils.isEmpty(outputChooser.getTextField()
								.getText())) {
					JOptionPane.showMessageDialog(MainFrame.this,
							"Please choose file");
					return;
				}

				FileInputStream fis = null;
				FileOutputStream fos = null;
				try {
					fis = new FileInputStream(inputChooser.getTextField()
							.getText());
					fos = new FileOutputStream(outputChooser.getTextField()
							.getText());
					InputStream input = null;
					if (encryptButton.isSelected()) {
						EncryptionInputStream eis = new EncryptionInputStream(
								fis);
						eis.setCipher(new Ass1Cipher());
						input = eis;
					} else {
						DecryptionInputStream dis = new DecryptionInputStream(
								fis);
						dis.setCipher(new Ass1Cipher());
						input = dis;
					}
					IOUtils.copy(input, fos);
					fis.close();
					fos.close();
					JOptionPane.showMessageDialog(MainFrame.this, "Done");
				} catch (IOException ex) {
					if (fis != null)
						try {
							fis.close();
						} catch (Exception iex) {
							throw new RuntimeException(iex);
						}
				}
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
