package ass3.program.ui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.text.DateFormat;
import java.text.MessageFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;
import javax.swing.border.LineBorder;

import ass3.program.core.MessageEvent;
import ass3.program.core.MessageListener;
import ass3.program.core.message.Message;
import ass3.program.core.message.SendTextRequest;

public class ChatFrame extends JFrame implements MessageListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -2562478628695724397L;

	String target;

	MainFrame parent;

	JTextArea historyArea;

	JTextArea inputArea;

	public ChatFrame(String target, MainFrame parent) {
		super();
		this.target = target;
		this.parent = parent;
		parent.getChatFrames().put(target, this);

		this.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosed(WindowEvent e) {
				ChatFrame.this.parent.getChatFrames().remove(
						ChatFrame.this.target);
				ChatFrame.this.parent.getChatter().dropChatter(
						ChatFrame.this.target);
			}
		});

		setTitle(MessageFormat.format("Chat with {0}", target));
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setSize(400, 600);

		setLayout(new BorderLayout());

		JSplitPane split = new JSplitPane(JSplitPane.VERTICAL_SPLIT);

		add(split, BorderLayout.CENTER);

		historyArea = new JTextArea();
		historyArea.setEditable(false);
		split.setLeftComponent(historyArea);

		JPanel downPanel = new JPanel();
		split.setRightComponent(downPanel);
		downPanel.setLayout(new BorderLayout());

		inputArea = new JTextArea();
		inputArea.setBorder(new LineBorder(Color.gray, 2));
		inputArea.addKeyListener(new KeyAdapter() {
			@Override
			public void keyReleased(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					String message = inputArea.getText();
					sendMessage(message.trim());
					inputArea.setText(null);
				}
			}
		});
		downPanel.add(inputArea, BorderLayout.CENTER);

		JPanel buttonPanel = new JPanel();
		buttonPanel.setPreferredSize(new Dimension(90, 50));
		downPanel.add(buttonPanel, BorderLayout.EAST);

		JButton sendButton = new JButton("Send");
		buttonPanel.add(sendButton);
		sendButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				sendMessage(inputArea.getText());
				inputArea.setText(null);
			}
		});

		doLayout();
		setVisible(true);
		split.setDividerLocation(0.8);
	}

	public void sendMessage(String text) {
		attachText(ME, text);
		parent.getChatter().send(target, text);
	}

	@Override
	public void messageReceived(MessageEvent event) {
		Message msg = event.getContent();
		if (msg instanceof SendTextRequest && msg.getFrom().equals(this.target)) {
			// Receive a message
			SendTextRequest str = (SendTextRequest) msg;
			final String text = str.getText();
			SwingUtilities.invokeLater(new Runnable() {
				public void run() {
					attachText(target, text);
				}
			});
		}
	}

	public static final String ME = "Me";

	protected static final DateFormat dateFormat = new SimpleDateFormat("HH:mm");

	protected void attachText(String author, String content) {
		historyArea.append(MessageFormat.format("{0}  {1}:\n{2}\n", author,
				dateFormat.format(new Date()), content));
	}
}
