import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.SocketException;

public class ServerThread implements Runnable {
    private final ObjectOutputStream OUTPUT_STREAM;
    private final ObjectInputStream INPUT_STREAM;
    private int clientID;

    ServerThread(Socket socket) throws IOException, ClassNotFoundException {
        this.INPUT_STREAM = new ObjectInputStream(socket.getInputStream());
        this.OUTPUT_STREAM = new ObjectOutputStream(socket.getOutputStream());
        this.clientID = receiveClientID();
    }

    @Override
    public void run() {
        try {
            goOnline();
        } catch (IOException e) {
            e.printStackTrace();
        }

        readBufferedMessages();

        try {
            while (true) {
                sendMessage(getMessageFromClient());
            }
        } catch (EOFException | SocketException ignored) {
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }

        goOffline();
    }

    private void sendMessage(Message message) throws IOException {
        for(OrderedPair<Integer, ServerThread> pair: Server.getServerThreadList()) {
            if (message.getReceiverID() == pair.getKey()) {
                ServerThread serverThread = pair.getValue();
                if (serverThread != null)
                    serverThread.OUTPUT_STREAM.writeObject(message);

                else Server.getBufferedMessagesList().add(new OrderedPair<>(message.getReceiverID(), message));
                break;
            }
        }
    }

    private Message getMessageFromClient() throws IOException, ClassNotFoundException {
        return (Message) INPUT_STREAM.readObject();
    }

    private int getIndexOfMatchingServerThread(int size) {
        int i = 0;
        for (; i < size; i++) {
            if (Server.getServerThreadList().get(i).getKey() == this.clientID)
                break;
        }
        return i;
    }

    private int receiveClientID() throws IOException, ClassNotFoundException {
        return (int) INPUT_STREAM.readObject();
    }

    private void readBufferedMessages() {
        try {
            int i = 0;
            while (i < Server.getBufferedMessagesList().size()) {
                if (Server.getBufferedMessagesList().get(i).getKey() == this.clientID) {
                    this.OUTPUT_STREAM.writeObject(new Message(Server.getBufferedMessagesList().get(i).getValue()));
                    Server.getBufferedMessagesList().remove(i);
                } else i++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void goOnline() throws IOException {
        int i, size = Server.getServerThreadList().size();

        i = getIndexOfMatchingServerThread(size);

        if (i == size) {
            Server.addServerThread(new OrderedPair<>(this.clientID, this));

            sendProperIDsToClients(size, false);

            sendClientID(OUTPUT_STREAM, this.clientID, this.clientID);
        } else {
            Server.getServerThreadList().get(i).setValue(this);

            sendProperIDsToClients(size, true);
        }
    }

    private void sendClientID(ObjectOutputStream output, int key, int receiverID) throws IOException {
        output.writeObject(new Message(key, receiverID, true, ""));
    }

    private void sendProperIDsToClients(int size, boolean onlyToMyClient) throws IOException {

        for (int j = 0; j < size; j++) {
            OrderedPair<Integer, ServerThread> temp = Server.getServerThreadList().get(j);
            if(!onlyToMyClient) sendClientID(temp.getValue().OUTPUT_STREAM, this.clientID, temp.getKey());

            sendClientID(OUTPUT_STREAM, temp.getKey(), this.clientID);
        }
    }

    private void goOffline() {
        for (int i = 0; i < Server.getServerThreadList().size(); i++) {
            OrderedPair<Integer, ServerThread> pair = Server.getServerThreadList().get(i);
            if (pair.getKey() == this.clientID) {
                pair.setValue(null);
                break;
            }
        }

        try {
            INPUT_STREAM.close();
            if (OUTPUT_STREAM != null)
                OUTPUT_STREAM.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}
