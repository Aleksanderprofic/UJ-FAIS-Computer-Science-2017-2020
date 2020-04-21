import javax.swing.*;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class Client extends JFrame {

    private final int THISCLIENTID;
    private int sendMessageToThisID;

    private Socket socket;
    private ObjectOutputStream objectOutputStream;

    private TextPanel textPanel;
    private JTextArea chatArea;
    private JList<String> listOfClientIDs;

    private Client(int ID) throws IOException {
        this.sendMessageToThisID = ID;
        this.THISCLIENTID = ID;

        setParameters();
        addComponents();

        sendIDToServerThread();

        createAndStartReader();

        listOfClientIDs.getSelectionModel().addListSelectionListener(e -> {
            String temp;
            if ((temp = listOfClientIDs.getSelectedValue()) != null)
                sendMessageToThisID = Integer.parseInt(temp);
            else this.sendMessageToThisID = this.THISCLIENTID;
        });
    }

    private void addComponents() throws IOException {
        JLabel usersLabel = new JLabel("Users");
        JButton sendButton = new JButton("Send");
        socket = new Socket("localhost", Server.PORT);
        objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
        chatArea = new JTextArea();
        textPanel = new TextPanel(chatArea);
        listOfClientIDs = new JList<>();
        usersLabel.setHorizontalAlignment(SwingConstants.CENTER);

        chatArea.setEditable(false);
        chatArea.setLineWrap(true);
        chatArea.setBounds(0, 0, 375, 310);
        sendButton.setBounds(385, 330, 100, 40);
        textPanel.setBounds(0, 0, 385, 380);
        textPanel.getTextField().setBounds(2, 330, 381, 40);
        textPanel.getScrollPane().setBounds(5, 5, 375, 315);
        listOfClientIDs.setBounds(385, 35, 100, 285);
        usersLabel.setBounds(385, 5, 100, 25);

        this.add(sendButton);
        this.add(textPanel);
        this.add(listOfClientIDs);
        this.add(usersLabel);

        sendButton.addActionListener(e -> {
            String temp = textPanel.getTextField().getText();

            if (!temp.equals("")) {
                Message message = new Message(THISCLIENTID, sendMessageToThisID, false, temp);

                textPanel.getTextField().setText("");
                try {
                    if (this.THISCLIENTID != message.getReceiverID()) chatArea.append(this.THISCLIENTID + ": " + message.toString() + "\n");
                    objectOutputStream.writeObject(message);
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        });
    }

    private void sendIDToServerThread() throws IOException {
        objectOutputStream.writeObject(THISCLIENTID);
    }

    private void createAndStartReader() throws IOException {
        ClientReader reader = new ClientReader(this);
        reader.start();
    }

    private void setParameters() {
        this.setTitle("Client " + THISCLIENTID);
        this.setSize(500, 400);
        this.setLayout(null);
        this.setResizable(false);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }

    ObjectOutputStream getObjectOutputStream() {
        return objectOutputStream;
    }

    Socket getSocket() {
        return socket;
    }

    JTextArea getChatArea() {
        return chatArea;
    }

    JList<String> getListOfClientIDs() {
        return listOfClientIDs;
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("USAGE > java Client [id]");
            System.exit(-1);
        }

        SwingUtilities.invokeLater(() -> {
            try {
                new Client(Integer.parseInt(args[0]));
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }
}