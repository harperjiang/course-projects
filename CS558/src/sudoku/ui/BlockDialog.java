package sudoku.ui;

import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class BlockDialog extends JDialog {

	/**
	 * 
	 */
	private static final long serialVersionUID = -7159941446081118846L;

	public BlockDialog(JFrame parent) {
		super(parent);
		setSize(new Dimension(200, 100));
		setTitle("Processing...");
		setLocation(parent.getLocation().x + parent.getSize().width / 2
				- getSize().width / 2,
				parent.getLocation().y + parent.getSize().height / 2
						- getSize().height / 2);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setResizable(false);
		setUndecorated(true);
		setModal(true);
		setModalityType(ModalityType.APPLICATION_MODAL);

		setLayout(new FlowLayout());
		add(new JLabel("Processing...."));
		doLayout();
	}

}
