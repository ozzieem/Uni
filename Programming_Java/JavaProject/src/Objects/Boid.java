package Objects;

import javafx.scene.control.Label;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;

import java.io.Serializable;
import java.util.Random;

import static View.ServerGUI.*;

/**
 * The class for the boid
 * Contains constants for the rules
 * and some transient JavaFX objects so it is not serialized
 */
public class Boid implements Serializable {

    public static double MAX_VELOCITY = 2.0;
    private static final double MAX_FORCE = 0.5;
    private static final double MIN_VELOCITY = -MAX_VELOCITY;

    // Constants for rules
    // These values was set by visually observing the behaviour of the flock
    public static double COHESION_WEIGHT = 0.2;
    public static double SEPARATION_WEIGHT = 0.05;
    public static double ALIGNMENT_WEIGHT = 0.3;

    private final double COHESION_RATIO = 100;
    private final double SEPARATION_PERCEPTION = this.radius + 25;
    private final double ALIGNMENT_DISTANCE = 50;
    private final double COHESION_DISTANCE = 50;

    private static final Random rand = new Random();

    public final String name;
    public final double radius = 10;

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    transient public Circle body;
    transient public Line direction;
    transient public Label clientID;

    public Boid(String name) {
        this.position = new Vector2(this.getRandomRange(200, 600));
        this.velocity = (this.getRandomRange(MIN_VELOCITY, MAX_VELOCITY));
        this.acceleration = new Vector2();
        this.name = name;
    }

    /**
     * Updates position of the boid
     * @param flock The current server flock
     */
    public void Update(Flock flock) {
        Vector2 cohesion = cohesion(flock);
        Vector2 separation = separation(flock);
        Vector2 alignment = alignment(flock);

        this.velocity.add(cohesion);
        this.velocity.add(separation);
        this.velocity.add(alignment);
        this.velocity.limit(MAX_VELOCITY);
        this.position.add(this.velocity);

        this.AvoidEdges();
    }

    /**
     * Makes the boids move to center of mass of all other boids
     * @param flock Current flock on server
     * @return A vector to the perceived center
     */
    private Vector2 cohesion(Flock flock) {

        Vector2 perceivedCentre = new Vector2();
        int count = 0;

        for (Boid other : flock.getList()) {
            if (other != this) {
                double d = this.position.distance(other.position);
                if ((d > 0) && (d < COHESION_DISTANCE)) {
                    perceivedCentre.add(other.position);
                    count++;
                }
            }
        }

        if (count > 0) {
            perceivedCentre.divide(count);
            perceivedCentre.subtract(this.position);
            perceivedCentre.divide(COHESION_RATIO);
            perceivedCentre.multiply(COHESION_WEIGHT);
        }
        return perceivedCentre;
    }

    /**
     * Separates the boid from other nearby boids
     * @param flock Current server flock
     * @return A vector away from the nearest boids
     */
    private Vector2 separation(Flock flock) {

        Vector2 separate = new Vector2();

        for (Boid other : flock.getList()) {
            if (other != this) {
                double distance = other.position.distance(this.position);
                if (distance > 0 && distance < SEPARATION_PERCEPTION) {
                    Vector2 diff = new Vector2(other.position);
                    diff.subtract(this.position);
                    separate.subtract(diff);
                }
            }
        }
        separate.multiply(SEPARATION_WEIGHT);
        return separate;
    }

    /**
     * Adjusts velocity according to nearby boids
     * @param flock Current server flock
     * @return A vector with the average speed of all nearby boids
     */
    private Vector2 alignment(Flock flock) {

        Vector2 perceivedVelocity = new Vector2();
        int count = 0;

        for (Boid other : flock.getList()) {
            if (other != this) {
                double d = this.position.distance(other.position);
                if ((d > 0) && (d < ALIGNMENT_DISTANCE)) {
                    perceivedVelocity.add(other.velocity);
                    count++;
                }
            }
        }

        if (count > 0) {
            perceivedVelocity.divide(count);
            perceivedVelocity.subtract(this.velocity);
            perceivedVelocity.normalize();
            perceivedVelocity.multiply(ALIGNMENT_WEIGHT);
        }
        return perceivedVelocity;
    }

    /**
     * Avoid the edges of the window
     */
    private void AvoidEdges() {
        Vector2 oppositeVec = new Vector2(0);
        // Window Right Edge
        if (this.position.x > MAINPANE_W - BORDER_OFFSET) {
            oppositeVec = new Vector2(MIN_VELOCITY, this.velocity.y);
        }
        // Window Bottom Edge
        if (this.position.y > MAINPANE_H - BORDER_OFFSET) {
            oppositeVec = new Vector2(this.velocity.x, MIN_VELOCITY);
        }
        // Window Left Edge
        if (this.position.x < BORDER_OFFSET) {
            oppositeVec = new Vector2(MAX_VELOCITY, this.velocity.y);
        }
        // Window Top Edge
        if (this.position.y < BORDER_OFFSET) {
            oppositeVec = new Vector2(this.velocity.x, MAX_VELOCITY);
        }

        if (oppositeVec.x != 0 && oppositeVec.y != 0) {
            this.SmoothTurn(oppositeVec);
        }
    }

    /**
     * Creates a smooth turn away from the window edges
     * @param target The vector facing away from the window edge
     */
    private void SmoothTurn(Vector2 target) {
        target.subtract(this.velocity);
        target.limit(MAX_FORCE);
        this.velocity.add(target);
    }

    /**
     * Sets the JavaFX objects to the updated values
     * @param flockGUI Current server flock
     */
    public void Draw(Flock flockGUI) {
        this.Update(flockGUI);

        this.body.setCenterX(this.position.x);
        this.body.setCenterY(this.position.y);

        this.direction.setStartX(this.position.x);
        this.direction.setStartY(this.position.y);

        double lineExtenderFactor = 10.0;
        this.direction.setEndX(this.position.x + this.velocity.x * lineExtenderFactor);
        this.direction.setEndY(this.position.y + this.velocity.y * lineExtenderFactor);

        this.clientID.setText(this.name);
        this.clientID.setTranslateX(this.position.x - 5);
        this.clientID.setTranslateY(this.position.y - 10);
    }

    /**
     * Used to place the boid on a random position on the screen
     * @param min Minimum spawn value
     * @param max Maximum spawn value
     * @return A value between min and max value
     */
    private Vector2 getRandomRange(double min, double max) {
        double x = min + (rand.nextDouble() * (max - min));
        double y = min + (rand.nextDouble() * (max - min));
        return new Vector2(x, y);
    }

    @Override
    public String toString() {
        return ("p: " + this.position.toString() + " " + "v: " + this.velocity.toString());
    }
}
