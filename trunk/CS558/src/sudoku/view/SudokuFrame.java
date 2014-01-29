package sudoku.view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

import javax.swing.AbstractAction;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JToolBar;
import javax.swing.SwingUtilities;

import sudoku.model.SudokuModel;
import common.exec.z3.Z3Executor;

public class SudokuFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6275020573594671300L;

	private JPanel centerPanel;

	private SudokuModel model = new SudokuModel(3);

	/**
	 * @param args
	 */
	public SudokuFrame() {
		setTitle("Sudoku");
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setLayout(new BorderLayout());

		add(generateToolBar(), BorderLayout.NORTH);

		centerPanel = new JPanel();
		FlowLayout flow = new FlowLayout();
		flow.setHgap(1);
		flow.setVgap(1);
		centerPanel.setLayout(flow);

		add(centerPanel, BorderLayout.CENTER);
		rearrangeGrid();

		setVisible(true);
	}

	protected void rearrangeGrid() {
		int size = model.getWidth();
		int preferredSize = (50 + 2) * size;
		setSize(new Dimension(preferredSize, preferredSize + 80));
		centerPanel.removeAll();
		for (int i = 0; i < size * size; i++) {
			NumberButton nb = new NumberButton(i);
			nb.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					String input = JOptionPane.showInputDialog(
							SudokuFrame.this, "Input Number For this val");
					try {
						int val = Integer.parseInt(input);
						int size = model.getWidth();
						NumberButton button = (NumberButton) e.getSource();
						int index = button.getIndex();
						model.setNumber(index / size, index % size, val);
						button.setText(input);
					} catch (IllegalStateException exception) {
						JOptionPane.showMessageDialog(SudokuFrame.this,
								"Please reset to start new game", "Need Reset",
								JOptionPane.ERROR_MESSAGE);
					} catch (IllegalArgumentException exception) {
						JOptionPane.showMessageDialog(SudokuFrame.this,
								"Invalid Number", "Invalid Number",
								JOptionPane.ERROR_MESSAGE);
					} catch (Exception exception) {
						JOptionPane.showMessageDialog(SudokuFrame.this,
								"Invalid Number", "Invalid Number",
								JOptionPane.ERROR_MESSAGE);
					}
				}
			});
			centerPanel.add(nb);
		}
		centerPanel.doLayout();
	}

	protected JToolBar generateToolBar() {
		JToolBar toolBar = new JToolBar();
		toolBar.add(new AbstractAction("Setting") {
			/**
			 * 
			 */
			private static final long serialVersionUID = 9080171741285023506L;

			@Override
			public void actionPerformed(ActionEvent e) {
				String input = JOptionPane.showInputDialog(SudokuFrame.this,
						"Input Size(2-10)");
				try {
					int value = Integer.parseInt(input);
					if (value < 2 || value > 10)
						throw new IllegalArgumentException();
					model.setSize(value);
					SudokuFrame.this.rearrangeGrid();
				} catch (NumberFormatException ex) {
					JOptionPane.showMessageDialog(SudokuFrame.this,
							"Not a valid number!");
				}
			}
		});
		toolBar.add(new AbstractAction("Solve") {
			/**
			 * 
			 */
			private static final long serialVersionUID = -3763555402878998957L;

			@Override
			public void actionPerformed(ActionEvent e) {
				final BlockDialog block = new BlockDialog(SudokuFrame.this);
				// Create a thread to execute

				Thread thread = new Thread() {
					public void run() {
						try {
							final Map<String, Object> values = SudokuFrame.this
									.solve();
							if (null == values) {
								JOptionPane.showMessageDialog(SudokuFrame.this,
										"Cannot Solve this. Please reset.");
								return;
							}
							SwingUtilities.invokeAndWait(new Runnable() {
								public void run() {
									int val = model.getWidth();
									val *= val;
									for (int i = 0; i < val; i++) {
										NumberButton nb = (NumberButton) centerPanel
												.getComponent(i);
										int result = (Integer) values
												.get("var_" + i);
										nb.setText(String.valueOf(result));
									}
								}
							});
						} catch (IllegalStateException e) {
							JOptionPane.showMessageDialog(SudokuFrame.this,
									"Please reset to start a new game");
						} catch (Exception e) {
							JOptionPane.showMessageDialog(SudokuFrame.this,
									"Cannot Solve this. Please reset.");
						} finally {
							SwingUtilities.invokeLater(new Runnable() {
								public void run() {
									block.setVisible(false);
								}
							});
						}
					}
				};
				thread.start();

				block.setVisible(true);

			}
		});
		toolBar.add(new AbstractAction("Reset") {
			/**
			 * 
			 */
			private static final long serialVersionUID = 6030131870109218735L;

			@Override
			public void actionPerformed(ActionEvent e) {
				model.reset();
				SudokuFrame.this.rearrangeGrid();
				SudokuFrame.this.repaint();
			}
		});
		return toolBar;
	}

	@Override
	public void print(Graphics g) {
		super.print(g);
	}

	protected Map<String, Object> solve() {
		Map<String, Object> result = new HashMap<String, Object>();
		boolean solvable = new Z3Executor().execute(model, result);
		if (solvable)
			return result;
		return null;
	}

	public static void main(String[] args) {
		new SudokuFrame();
	}
}
