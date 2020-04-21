import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Server {
    static final int PORT = 10003;
    private static ArrayList<OrderedPair<Integer, ServerThread>> serverThreadList = new ArrayList<>();
    private static ArrayList<OrderedPair<Integer, Message>> bufferedMessagesList = new ArrayList<>();

    static ArrayList<OrderedPair<Integer, ServerThread>> getServerThreadList() {
        return serverThreadList;
    }

    static ArrayList<OrderedPair<Integer, Message>> getBufferedMessagesList() {
        return bufferedMessagesList;
    }

    static void addServerThread(OrderedPair<Integer, ServerThread> newServerThread) {
        serverThreadList.add(newServerThread);
    }

    public static void main(String[] args) {
        runServer();
    }

    private static void runServer() {
        try {
            ServerSocket serverSocket = new ServerSocket(PORT);

            System.out.println("Server is up & ready to go");
            Socket socket;

            while(true) {
                socket = serverSocket.accept();
                System.out.println("New client request received : " + socket);

                createAndRunServerThread(socket);
            }
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    private static void createAndRunServerThread(Socket socket) throws IOException, ClassNotFoundException {
        ServerThread serverThread = new ServerThread(socket);

        Thread thread = new Thread(serverThread);

        thread.start();
    }
}
