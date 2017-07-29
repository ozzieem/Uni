package Objects;

import java.io.Serializable;
import java.text.DecimalFormat;

/**
 * Custom-made vector class for easier
 * implementation of necessary methods
 * and keeping only needed ones
 */
public class Vector2 implements Serializable {

    double x;
    double y;

    public Vector2() {
        this.x = 0;
        this.y = 0;
    }

    public Vector2(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Vector2(Vector2 vec) {
        this.equals(vec);
    }

    public Vector2(double value) {
        this.x = value;
        this.y = value;
    }

    private void equals(Vector2 vec) {
        this.x = vec.x;
        this.y = vec.y;
    }

    public void add(Vector2 vec) {
        this.x += vec.x;
        this.y += vec.y;
    }

    public void subtract(Vector2 vec) {
        this.x -= vec.x;
        this.y -= vec.y;
    }

    public void multiply(double value) {
        this.x *= value;
        this.y *= value;
    }

    public void divide(double value) {
        this.x /= value;
        this.y /= value;
    }

    public void limit(double value) {
        if (value > 0 || value < 0) {
            while (this.x < -value || this.y < -value) {
                this.divide(2);
            }

            while (this.x > value || this.y > value) {
                this.divide(2);
            }
        }
    }

    public double distance(Vector2 target) {
        double dy = target.y - this.y;
        double dx = target.x - this.x;
        return Math.sqrt(dx * dx + dy * dy);
    }

    public void normalize() {
        double length = distance(this);
        if (length > 0) {
            this.divide(length);
        }
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }

    @Override
    public String toString() {
        DecimalFormat df = new DecimalFormat("#.00");
        return "(" + df.format(x) + " | " + df.format(y) + ")";
    }
}
