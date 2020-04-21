package balls;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Ball extends Thread {
    private static double XSPEED, YSPEED;
    private double xSpeed, ySpeed;
    private int x, y, oldX, oldY;
    private Color color;
    private GraphicsContext gc;
    private boolean isOutside, isMiddle;
    private Box box;
    private double limitLeft, limitRight, limitUp, limitDown;
    private double x1b, x2b, y1b, y2b;

    static {
        XSPEED = -1.8;
        YSPEED = 2;
    }

    Ball(GraphicsContext gc, Box box) {
        this.xSpeed = genRandomDir() * XSPEED;
        this.ySpeed = genRandomDir() * YSPEED;
        this.gc = gc;
        color = genColor();
        x = 400;
        y = 370;
        this.isOutside = true;
        this.isMiddle = false;
        this.box = box;
        limitUp = 0;
        limitDown = 500;
        limitRight = 574;
        limitLeft = 0;
        x1b = box.getX();
        x2b = box.getX() + box.getWidth();
        y1b = box.getY();
        y2b = box.getY() + box.getHeight();
    }

    private Color genColor() {
        return new Color(Math.random(), Math.random(), Math.random(), 1);
    }

    private double genRandomDir() {
        int temp = (int) (Math.random() * 2);
        if (temp == 1) return 1;
        else return -1;
    }

    private void checkInside() {
        // Jeżeli wyjdzie poza kwadrat
        if ((x < (x1b - 10) || x > (x2b + 10)) || (y < (y1b - 10) || y > (y2b + 10))) {
            isOutside = true;
            isMiddle = false;
        }
        // Jeżeli wejdzie do kwadratu
        else if (x > (x1b + 10) && x < (x2b - 10) && y > (y1b + 10) && y < (y2b - 10)) {
            isMiddle = false;
            changeLimit();
        }
    }

    private void collision() {
        if ((x >= x1b - 5 && x <= x2b + 5) &&
                (y >= y1b - 5 && y <= y2b + 5)) {
            isOutside = false;
            synchronized (box) {
                try {
                    box.wait();
                    checkInside();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            isMiddle = true;
        }
    }

    @Override
    public void run() {
        while (!Playground.end) {
            if (isOutside) collision();
            if (isMiddle) checkInside();
            draw();
            move();

            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private void draw() {
        synchronized (gc) {
            gc.setFill(Color.WHITE);
            gc.setStroke(Color.WHITE);
            gc.fillOval(oldX - 10.5, oldY - 10.5, 21, 21);
            gc.setFill(color);
            // -10 ponieważ rysuje piłkę przyklejoną do punktu (x, y) od dołu z prawej strony
            gc.fillOval(x - 10, y - 10, 20, 20);
        }
    }

    private void move() {
        oldX = x;
        oldY = y;
        x += xSpeed;
        y += ySpeed;

        if (x >= (limitRight - 10) || x <= (limitLeft + 10)) xSpeed = -xSpeed;
        if (y >= (limitDown - 10) || y <= (limitUp + 10)) ySpeed = -ySpeed;
    }

    private void changeLimit() {
        this.limitLeft = this.x1b;
        this.limitRight = this.x2b;
        this.limitUp = this.y1b;
        this.limitDown = this.y2b;
    }
}