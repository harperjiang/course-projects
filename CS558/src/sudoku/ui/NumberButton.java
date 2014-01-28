package sudoku.ui;

import java.awt.Dimension;
import java.awt.Font;

import javax.swing.JButton;

public class NumberButton extends JButton {
	/**
	 * 
	 */
	private static final long serialVersionUID = -7564018057338800979L;

	private static Font font = new Font("Verdana", Font.PLAIN, 12);

	private int index;

	public NumberButton(int index) {
		super();
		setPreferredSize(new Dimension(50, 50));

		setFont(font);
		this.index = index;
	}

	public int getIndex() {
		return index;
	}

	public void setIndex(int index) {
		this.index = index;
	}

}
