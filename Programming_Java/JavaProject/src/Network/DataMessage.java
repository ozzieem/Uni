package Network;


import Objects.Boid;
import Objects.Flock;

import java.io.Serializable;

/**
 * A class for easier sending objects between server and client
 */
public class DataMessage implements Serializable {

    private String clientName;
    private Flock flock;
    private Boid boid;

    public DataMessage(Boid boid) {
        this.boid = boid;
    }

    public DataMessage(Flock flock) { this.flock = flock; }

    public DataMessage(String name) {
        this.clientName = name;
    }


    public String getName() {
        return clientName;
    }

    public Boid getBoid() {
        return boid;
    }

    public Flock getFlock() {
        return flock;
    }
}
