import java.io.Serializable;

public class Message implements Serializable {
    private final int senderID;
    private int receiverID;
    boolean isNewID;
    private String message;

    int getSenderID() {
        return senderID;
    }

    int getReceiverID() {
        return receiverID;
    }

    Message(int senderID, int receiverID, boolean isNewID, String message) {
        this.senderID = senderID;
        this.receiverID = receiverID;
        this.isNewID = isNewID;
        this.message = message;
    }

    Message(Message message) {
        this.senderID = message.getSenderID();
        this.receiverID = message.getReceiverID();
        this.isNewID = false;
        this.message = message.toString();
    }

    public String toString() {
        return this.message;
    }
}
