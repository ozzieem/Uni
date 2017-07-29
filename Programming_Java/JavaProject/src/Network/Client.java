package Network;


import Objects.Boid;
import Objects.Flock;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.UUID;

/**
 * The client responsible for updated the received boid from the server
 */
public class Client {

    private ObjectInputStream inputStream;
    private ObjectOutputStream outputStream;
    private Socket socket;
    private InetAddress url;

    private Flock serverFlock;
    private final String name;
    private final int port;
    private Boid boid;

    private Client(String name) {
        try {
            this.url = InetAddress.getByName("localhost");
        } catch (UnknownHostException e) {
            System.out.println("");
        }

        this.serverFlock = new Flock();
        this.boid = new Boid("");

        this.name = name;
        this.port = 3000;
    }

    /**
     * Initializes all connections, streams and the listening thread
     * @return If everything went well, it returns true, otherwise false
     */
    public boolean init() {

        if (!setupConnection()) return false;
        if (!setupStreams()) return false;
        if (!initClient()) return false;
        initServerListener();

        return true;
    }

    /**
     * Creates and initializes the listener thread
     * on the client for incoming objects from the server
     */
    public void initServerListener() {
        // Listens for a message from server
        System.out.println("[LOG] Creating server-listener");
        (new Thread(new ReceiveFromServer())).start();
        System.out.println("[LOG] Server-listener created");
    }

    /**
     * Sends the client ID to the server and
     * receives its boid from the server
     * @return Confirmation bool
     */
    public boolean initClient() {
        // Sending clientname to server
        if (!this.sendData(new DataMessage(this.name)))
            return false;
        DataMessage dataMessage = this.readData();
        this.boid = dataMessage.getBoid();
        System.out.println("[LOG] Client received first boid: " + this.boid.toString());
        return true;
    }

    /**
     * Sets up the streams on the socket established with the server
     * @return Confirmation bool
     */
    public boolean setupStreams() {
        try {
            System.out.println("[LOG] Attempting to create IO-streams");
            this.outputStream = new ObjectOutputStream(this.socket.getOutputStream());
            this.inputStream = new ObjectInputStream(this.socket.getInputStream());
            System.out.println("[LOG] IO-streams created");
        } catch (IOException e) {
            System.out.println("[ERROR] Unable to create streams to server. Disconnecting... - " + e.getMessage());
            return false;
        }
        return true;
    }

    /**
     * Attempts to establish a connection with the server
     * @return Confirmation bool
     */
    public boolean setupConnection() {
        try {
            System.out.println("[LOG] Attempting to connect to server as " + name);
            this.socket = new Socket(this.url, this.port);
            System.out.println("[LOG] Connected to server on " + this.url + ":" + this.port);
        } catch (IOException e) {
            System.out.println("[ERROR] Could not establish connection to server - " + e.getMessage());
            return false;
        }
        return true;
    }

    public boolean sendData(DataMessage dataMessage) {
        try {
            this.outputStream = new ObjectOutputStream(this.socket.getOutputStream());
            this.outputStream.writeObject(dataMessage);
            this.outputStream.flush();
        } catch (IOException e) {
            System.out.println("[ERROR] Unable to send data to server - " + e.getMessage());
            return false;
        }
        return true;
    }

    public DataMessage readData() {
        try {
            return (DataMessage) this.inputStream.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("[ERROR] Unable to read data from server - " + e.getMessage());
            System.exit(1);
        }
        return null;
    }

    public void disconnect() {
        try {
            this.outputStream.close();
            this.inputStream.close();
            this.socket.close();
        } catch (IOException e) {
            System.out.println("[ERROR] Error when closing streams and socket - " + e.getMessage());
        }
    }

    /**
     * Listens for incoming flock object from the server
     * Client is then updating its own boid depending on that flock
     * and sends it back to the server
     */
    class ReceiveFromServer implements Runnable {

        @Override
        public void run() {
            while (true) {
                try {
                    // Receive flock data
                    DataMessage flockData = readData();
                    serverFlock = serverFlock.equals(flockData.getFlock());

                    // Update the boid according to flock and send back to server
                    boid.Update(serverFlock);
                    sendData(new DataMessage(boid));

                } catch (IndexOutOfBoundsException e) {
                    System.out.println("[ERROR] " + e.getMessage());
                }
            }
        }
    }

    public static void main(String[] args) {

        String clientID = UUID.randomUUID().toString().substring(0, 3);
        Client client = new Client(clientID);

        if (!client.init()) {
            client.disconnect();
        }
    }

}