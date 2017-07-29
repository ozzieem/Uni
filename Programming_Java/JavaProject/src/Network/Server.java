package Network;

import Objects.Boid;
import Objects.Flock;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

/**
 * The server is running a listener thread for incoming connections
 * A simulation thread, for updating boids at the clients
 * And callable threads for each connected server
 */
public class Server {

    private final ArrayList<String> Clients;
    private ServerSocket serverSocket;
    private final ExecutorService serverPool;
    private final ExecutorService clientPool;
    private final List<Callable<Boid>> clientCallables;

    private final int port;
    private final Flock serverFlock;
    public boolean active;
    public boolean SIM_RUNNING = true;

    public Server() {
        this.port = 3000;
        // TODO: Perhaps make this into a class with its own methods (remove, add)..
        this.Clients = new ArrayList<>();
        this.active = false;
        this.serverPool = Executors.newCachedThreadPool();
        this.clientPool = Executors.newCachedThreadPool();
        this.clientCallables = new ArrayList<>();

        this.serverFlock = new Flock();

        this.startListener();
        this.initSimulation();
    }

    /**
     * Creates a listener thread
     */
    public void startListener() {
        Runnable listener = () -> {
            try {
                this.active = true;
                this.serverSocket = new ServerSocket(port);
                this.serverSocket.setReuseAddress(true);

                // waiting for connections
                System.out.println("[LOG] Server listening on port " + port);
                while (this.active) {
                    handleClientConnection(serverSocket.accept());
                }
            } catch (IOException e) {
                System.out.println("[ERROR] Unable to setup server - " + e.getMessage());
                close();
                this.active = false;
            }
        };
        serverPool.submit(listener);
    }

    /**
     * Initiates the simulation thread
     */
    public void initSimulation() {
        serverPool.submit(new simulationRunner());
    }

    /**
     * Creates a new clientThread and adds it to the clientCallables list
     * @param socket Returned socket from the connection
     */
    public void handleClientConnection(Socket socket) {
        ClientThread clientThread = new ClientThread(socket);
        clientCallables.add(clientThread);
    }

    /**
     * Runs the simulation indefinitely. Invokes all the available threads on
     * the clientCallables and adds the values from the Future list, on the
     * serverFlock list, to update the boids in the simulation.
     */
    public class simulationRunner implements Runnable {
        @Override
        public void run() {
            while (true) {
                if (SIM_RUNNING) {
                    try {
//                    System.out.println("Invoking all clientCallables: " + clientCallables.size());
                        List<Future<Boid>> futures = clientPool.invokeAll(clientCallables);

                        // Copy received boids to global boids
                        for (int i = 0; i < getServerFlock().size(); ++i) {
                            for (Future<Boid> future : futures) {
                                try {
                                    synchronized (serverFlock) {
                                        if (getServerFlock().getList().get(i).name == future.get().name) {
                                            getServerFlock().getList().set(i, future.get());
                                        }
                                    }
                                } catch (ExecutionException e) {
                                    e.printStackTrace();
                                }
                            }
                        }
                        Thread.sleep(50);
                    } catch (InterruptedException e) {
                        System.out.println("[ERROR] Simulationrunner closed unexpectedly." + e.getMessage());
                        System.exit(1);
                    }
                }
            }
        }
    }

    /**
     * Closes the serverSocket and the running threads
     */
    public void close() {
        try {
            if (serverSocket != null && !serverSocket.isClosed()) {
                serverSocket.close();
            }
            if (!serverPool.isShutdown()) {
                serverPool.shutdown();
            }
            if (!clientPool.isShutdown()) {
                clientPool.shutdown();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Accesses the serverFlock safely from threads
     * @return the Flock-list on the server
     */
    public synchronized Flock getServerFlock() {
        return serverFlock;
    }

    /**
     * Callable thread is created when a client connects.
     * It is invoked in the simulationThread and sends the server flock and
     * updates the corresponding boid for the client
     * The updated boid is received and returned as a Future in the simulationThread
     */
    public class ClientThread implements Callable {

        int id;
        String name;

        final Socket socket;
        ObjectInputStream inputStream;
        ObjectOutputStream outputStream;

        ClientThread(Socket socket) {
//        id = socket.id
            this.socket = socket;

            try {
                this.outputStream = new ObjectOutputStream(this.socket.getOutputStream());
                this.inputStream = new ObjectInputStream(this.socket.getInputStream());

                DataMessage data = this.readData();
                this.name = data.getName();
                System.out.println("[LOG] Client " + this.name + " connected.");
                Clients.add(this.name);
                System.out.println("[LOG] Online clients: " + Clients.toString());

                // Create boid for the connected client
                Boid boid = new Boid(this.name);
                this.sendData(new DataMessage(boid));
                getServerFlock().add(boid);
                System.out.println("[LOG] Sent first boid to " + this.name + ": " + boid);
                getServerFlock().printPositions();

            } catch (IOException e) {
                System.out.println("[ERROR] Client " + this.name + " disconnected");
                this.close();
            }
        }

        public DataMessage readData() {
            try {
                this.inputStream = new ObjectInputStream(this.socket.getInputStream());
                return (DataMessage) this.inputStream.readObject();
            } catch (IOException | ClassNotFoundException e) {
                System.out.println("[ERROR] Could not retrieve message from " + this.name + ". " + e.getMessage());
                this.close();
            }
            return null;
        }

        public void sendData(DataMessage data) {
            try {
                this.outputStream.writeObject(data);
                this.outputStream.flush();
//                System.out.println("[LOG] Sent flock " + this.clientFlock.getList().getList(0) + " to socket: " + this.socket);
            } catch (IOException e) {
                System.out.println("[ERROR] Could not send data to " + this.name + ". " + e.getMessage());
                this.close();
            }
        }

        public void close() {
            try {
                if (Clients.contains(this.name)) {
                    Clients.remove(this.name);
                }
                System.out.println("[LOG] Online clients: " + Clients.toString());
                synchronized (serverFlock) {
                    for (Boid boid : getServerFlock().getList()) {
                        if (boid.name.equals(this.name)) {
                            getServerFlock().getList().remove(boid);
                        }
                    }
                    clientCallables.remove(this);
                }

                if (this.outputStream != null) this.outputStream.close();
                if (this.inputStream != null) this.inputStream.close();
                if (this.socket != null && this.socket.isConnected()) this.socket.close();
            } catch (IOException e) {
                System.out.println("[ERROR] Unable to close thread for " + this.name + " - " + e.getMessage());
            }
        }

        /**
         * Sends the current flock on the server to the client.
         * Client boid is updated on the client and sent back to the server.
         * @return The updated boid as a Future in the simulationThread
         */
        @Override
        public Object call() {
            while (active) {
                try {
                    // Send the serverflock to client
                    this.sendData(new DataMessage(getServerFlock()));

                    // Receive the updated boid and return it as future
                    DataMessage receivedData = this.readData();
                    return receivedData.getBoid();

                } catch (NullPointerException np) {
                    System.out.println(np.getMessage());
                    break;
                }
            }
            return new Boid("");
        }
    }


    public static void main(String[] args) {
        try {
            Server server = new Server();
        } catch (Exception e) {
            System.out.println("[ERROR] Unable to initialize server. " + e);
        }
    }
}
