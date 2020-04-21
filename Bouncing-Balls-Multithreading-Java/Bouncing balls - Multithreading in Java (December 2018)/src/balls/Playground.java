package balls;

import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.effect.BlendMode;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;


public class Playground {
    static boolean end = false;
    @FXML
    private Canvas canvas;
    private GraphicsContext gc;

    public Rectangle box;

    public void initialize() {
        gc = canvas.getGraphicsContext2D();
        box.setStroke(Color.BLACK);
        box.setFill(Color.rgb(255,255,255,0.3));
        box = new Box(100, 100,250,250);
        System.out.println(box.getX() + " " + box.getY() + " " + box.getWidth() + " " + box.getHeight());
        clear(gc);
    }

    private void clear(GraphicsContext gc) {
        gc.setGlobalBlendMode(BlendMode.SRC_OVER);
        gc.setFill(Color.WHITE);
        gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
    }

    @FXML
    private void addBall() {
        Ball ball = new Ball(gc, (Box)box);
        Thread newBall = new Thread(ball);
        newBall.start();
    }

    @FXML
    void end() {
        end = true;
        clear(gc);
        gc.setStroke(Color.BLACK);
        gc.strokeText("Close the application", 50, 50);
    }

    @FXML
    void enter() {
        synchronized (box) {
            ((Box)box).enter();
        }
    }
}