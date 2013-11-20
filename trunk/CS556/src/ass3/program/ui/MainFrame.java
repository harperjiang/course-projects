package ass3.program.ui;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

import ass3.program.core.Chatter;

public class MainFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6180672899845198036L;

	private JTextField ipField;

	private Map<String, ChatFrame> chatFrames;

	private Chatter chatter;

	public MainFrame() {
		super();
		// Data Init
		chatFrames = new HashMap<String, ChatFrame>();
		chatter = new Chatter();

		// UI Init
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(new Dimension(300, 200));
		setResizable(false);
		setTitle("Chatter");

		setLayout(new FlowLayout());

		add(new JLabel("Input IP to chat:"));
		ipField = new JTextField();
		ipField.setPreferredSize(new Dimension(200, 25));
		add(ipField);

		JButton chatButton = new JButton("Start Chat");
		add(chatButton);
		chatButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				String ipData = ipField.getText();
				// TODO Verify the input data
				// Create a new chat window
				if (chatFrames.containsKey(ipData)) {
					ChatFrame existed = chatFrames.get(ipData);
					existed.setVisible(true);
					existed.toFront();
				} else {
					new ChatFrame(ipData, MainFrame.this);
				}
			}
		});

		setVisible(true);
	}

	protected Map<String, ChatFrame> getChatFrames() {
		return chatFrames;
	}

	protected Chatter getChatter() {
		return chatter;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new MainFrame();
	}

}
