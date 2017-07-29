package View;

import Network.Server;
import Objects.Boid;
import Objects.Flock;
import Objects.Vector2;
import javafx.animation.AnimationTimer;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.stage.Stage;
import javafx.util.Duration;

import static Objects.Boid.*;

public class ServerGUI extends Application {

    private static final double SCENE_W = 1000;
    private static final double SCENE_H = 800;
    private final double HBOX_W = 100;
    private static final double HBOX_H = 20;
    public static final double MAINPANE_H = SCENE_H - HBOX_H - 18;
    public static final double MAINPANE_W = SCENE_W;
    public static final double BORDER_OFFSET = 50;

    private Server serverConnection = new Server();
    private Flock flockGUI = new Flock();
    private boolean FLOCK = true;

    private Pane canvas;
    private AnimationTimer updater;

    private final TextField tFCohesion = new TextField("");
    private final TextField tFSeparation = new TextField("");
    private final TextField tFAlignment = new TextField("");
    private final TextField tFVelocity = new TextField("");

    private final Label labelCohesion = new Label("Cohesion:");
    private final Label labelSeparation = new Label("Separation:");
    private final Label labelAlignment = new Label("Alignment:");

    private final Label labelTime = new Label("Time: ");
    private final Label labelBoids = new Label("Boids:");
    private final Label labelAvgSpeed = new Label();
    private final Label labelMouse = new Label();
    private final Label labelVelocity = new Label("V: ");


    @Override
    public void start(Stage stage) throws Exception {
        if (!serverConnection.active)
            throw new Exception("Server lost connection");

        BorderPane root = new BorderPane();
        root.setCenter(addMainPane());
        root.setBottom(addInformationPane());

        // setup the scene
        Scene scene = new Scene(root, SCENE_W, SCENE_H);
        stage.setScene(scene);
        stage.show();
        System.out.println("[LOG] View.ServerGUI created");

        updateGUI();
    }

    /**
     * Adds a main scene to the BorderPane
     * @return Pane with the screen dimensions and a color
     */
    private Pane addMainPane() {
        this.canvas = new Pane();
        this.canvas.setPrefSize(MAINPANE_W, MAINPANE_H);
        this.canvas.setStyle("-fx-background-color: lightblue;");

        return canvas;
    }

    /**
     * Adds an HBox with the following controls:
     * PauseButton
     * ScatterButton
     * VelocityField for editing
     * WeightFields for editing boids
     * Timer label
     * Average Speed label
     * @return HBox with the listed values
     */
    private HBox addInformationPane() {
        HBox hbox = new HBox();
        hbox.setPadding(new Insets(5));
        hbox.setSpacing(8);

        addPauseButton(hbox);
        addScatterButton(hbox);
//        addMouseCoordinates();
        addVelocityField();
        addTimer();
        addWeightFields();

        // All all to the HBox
        hbox.getChildren().addAll(
                labelCohesion,
                tFCohesion,
                labelSeparation,
                tFSeparation,
                labelAlignment,
                tFAlignment,
                labelVelocity,
                tFVelocity,
                labelAvgSpeed,
                labelTime,
                labelBoids
        );

        return hbox;
    }

    private void addPauseButton(HBox hbox) {
        Button btnPause = new Button("Pause");
        btnPause.setPrefSize(HBOX_W, HBOX_H);
        btnPause.setOnMouseClicked(event -> {
            if (serverConnection.SIM_RUNNING) {
                updater.stop();
                btnPause.setText("Start");
                serverConnection.SIM_RUNNING = false;
            } else {
                updater.start();
                btnPause.setText("Pause");
                serverConnection.SIM_RUNNING = true;
            }
        });
        hbox.getChildren().add(btnPause);
    }

    private void addScatterButton(HBox hbox) {
        Button btnScatter = new Button("Scatter");
        btnScatter.setPrefSize(HBOX_W, HBOX_H);
        btnScatter.setOnMouseClicked(event -> {
            if (FLOCK) {
                COHESION_WEIGHT *= -1;
                ALIGNMENT_WEIGHT *= -1;
                btnScatter.setText("Flock");
                FLOCK = false;
            } else {
                COHESION_WEIGHT *= -1;
                ALIGNMENT_WEIGHT *= -1;
                btnScatter.setText("Scatter");
                FLOCK = true;
            }
        });
        hbox.getChildren().add(btnScatter);
    }

    private void addMouseCoordinates() {
        // Add mouse pointer location label
        Vector2 Mouse = new Vector2(0);
        labelMouse.setText(Mouse.toString());
        this.canvas.getChildren().add(labelMouse);
        this.canvas.setOnMousePressed(event -> {
            Mouse.setX(event.getX());
            Mouse.setY(event.getY());
            String msg = "(x: " + Mouse.getX() + ", y: " + Mouse.getY() + ")";
            labelMouse.setText(msg);
        });
    }

    private void addTimer() {
        // Add timer
        final int[] timer = {0};
        Timeline timeline = new Timeline();
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.getKeyFrames().add(new KeyFrame(Duration.seconds(1), event -> {
            if (serverConnection.SIM_RUNNING) {
                timer[0]++;
                labelTime.setText("Time: " + String.valueOf(timer[0]));
            }
        }));
        timeline.play();
    }

    private void addVelocityField() {
//        MAX_VELOCITY
        tFVelocity.setPrefWidth(50);
        tFVelocity.setText(String.valueOf(MAX_VELOCITY));

        tFVelocity.textProperty().addListener((observable, oldValue, newValue) -> {
            try {
                if (!(newValue == null) || !newValue.contains(",") || newValue.trim().isEmpty()) {
                    tFVelocity.setText(String.valueOf(newValue));
                    tFVelocity.textProperty().setValue(String.valueOf(newValue));
                    MAX_VELOCITY = Double.parseDouble(newValue);
                }
            } catch (NumberFormatException ignore) {
            }
        });
    }

    private void addWeightFields() {
        // TODO: Reduce code duplication..

        tFCohesion.setPrefWidth(50);
        tFSeparation.setPrefWidth(50);
        tFAlignment.setPrefWidth(50);

        tFCohesion.setText(String.valueOf(COHESION_WEIGHT));
        tFSeparation.setText(String.valueOf(SEPARATION_WEIGHT));
        tFAlignment.setText(String.valueOf(ALIGNMENT_WEIGHT));

        tFCohesion.textProperty().addListener((observable, oldValue, newValue) -> {
            try {
                if (!(newValue == null) || !newValue.contains(",") || newValue.trim().isEmpty()) {
                    tFCohesion.setText(String.valueOf(newValue));
                    tFCohesion.textProperty().setValue(String.valueOf(newValue));
                    COHESION_WEIGHT = Double.parseDouble(newValue);
                }
            } catch (NumberFormatException ignore) {
            }
        });

        tFSeparation.textProperty().addListener((observable, oldValue, newValue) -> {
            try {
                if (!(newValue == null) || !newValue.contains(",")) {
                    tFSeparation.setText(String.valueOf(newValue));
                    tFSeparation.textProperty().setValue(String.valueOf(newValue));
                    SEPARATION_WEIGHT = Double.parseDouble(newValue);
                }
            } catch (NumberFormatException ignore) {
            }
        });

        tFAlignment.textProperty().addListener((observable, oldValue, newValue) -> {
            try {
                if (!(newValue == null) || !newValue.contains(",")) {
                    tFAlignment.setText(String.valueOf(newValue));
                    tFAlignment.textProperty().setValue(String.valueOf(newValue));
                    ALIGNMENT_WEIGHT = Double.parseDouble(newValue);
                }
            } catch (NumberFormatException ignore) {
            }
        });
    }

    /**
     * Updates the canvas with the current boids on the server.
     * The GUI keeps its own Flock class, which is updated with
     * the one from the server.
     */
    private void updateGUI() {
        updater = new AnimationTimer() {
            @Override
            public void handle(long now) {
                try {
                    flockGUI = serverConnection.getServerFlock();

                    canvas.getChildren().clear();

                    for (Boid boid : flockGUI.getList()) {
                        boid.body = new Circle();
                        boid.direction = new Line();
                        boid.body.setFill(Color.AZURE);
                        boid.body.setRadius(boid.radius);
                        boid.clientID = new Label();

                        canvas.getChildren().add(boid.body);
                        canvas.getChildren().add(boid.direction);
                        canvas.getChildren().add(boid.clientID);
                    }

                    for (Boid boid : flockGUI.getList()) {
                        boid.Draw(flockGUI);
                    }

                    labelBoids.setText("Boids: " + flockGUI.size());
                    Vector2 avgSpeed = new Vector2();
                    if (flockGUI.getList() != null) {
                        avgSpeed = flockGUI.getAvgSpeed();
                        avgSpeed.multiply(10);
                    }
                    labelAvgSpeed.setText("AVG-Vel: (" +
                            String.valueOf((int) avgSpeed.getX()) + " | " +
                            String.valueOf((int) avgSpeed.getY()) + ")"
                    );

                    if (!serverConnection.active)
                        throw new Exception("Server lost connection");

                } catch (Exception np) {
                    System.out.println("[ERROR] Terminating View.ServerGUI: " + np.getMessage());
                    System.exit(1);
                }
            }
        };
        updater.start();
    }

    public static void main(String[] args) {
        try {
            launch(args);
        } catch (Exception e) {
            System.out.println("[ERROR] Exception occurred when launching GUI - " + e.getMessage());
            System.exit(1);
        }

    }
}
