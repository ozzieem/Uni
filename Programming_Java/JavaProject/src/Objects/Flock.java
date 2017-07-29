package Objects;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * A container to keep the boids in
 */
public class Flock implements Serializable {

    private List<Boid> boids = Collections.synchronizedList(new ArrayList<Boid>());


    public Flock() {
        boids = new ArrayList<>();
    }

    public void printPositions() {
        System.out.println("Flock:");
        boids.forEach(System.out::println);
        System.out.println("------END------");
    }

    public void add(Boid boid) {
        boids.add(boid);
    }

    public void clear() {
        boids.clear();
    }

    public int size() {
        return boids.size();
    }

    public List<Boid> getList() {
        return boids;
    }

    /**
     * Calculates the average speed of all boids in the container
     * @return The average speed of all boids
     */
    public Vector2 getAvgSpeed() {
        Vector2 avgSpeed = new Vector2();
        for (Boid boid : this.boids) {
            avgSpeed.add(boid.velocity);
        }
        avgSpeed.divide(boids.size());
        return avgSpeed;
    }

    public Flock equals(Flock other) {
        for (int boid = 0; boid < this.boids.size(); ++boid) {
            this.boids.get(boid).position = other.getList().get(boid).position;
            this.boids.get(boid).velocity = other.getList().get(boid).velocity;
            this.boids.get(boid).acceleration = other.getList().get(boid).acceleration;
        }
        return this;
    }
}
