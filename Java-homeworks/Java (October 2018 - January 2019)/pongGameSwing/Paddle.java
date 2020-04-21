package pongGameSwing;

import java.awt.*;

public class Paddle {
    private double y, speed;
    private final double SLOW = 0.90;
    private boolean upAccel, downAccel;
    private int player, x;

    public Paddle(int player) {
        upAccel = false; downAccel = false;
        y = 210; speed = 0;

        if(player == 1) x = 20;
        else x = 660;

        this.player = player;
    }

    public void draw(Graphics g) {
        if(player == 1) {
            g.setColor(Color.YELLOW);
        } else g.setColor(Color.CYAN);

        g.fillRect(x, getY(), 20, 80);
    }

    public void move() {
        if(upAccel) {
            speed -= 1;
        } else if(downAccel) {
            speed += 1;
        } else {
            speed *= SLOW;
        }

        if(speed >= 5) speed = 5;
        else if(speed <= -5) speed = -5;
        y += speed;

        if(y < 0) y = 0;
        else if (y > 420) y = 420;
    }

    public int getY() {
        return (int)y;
    }

    void setUpAccel(boolean input) {
        upAccel = input;
    }

    void setDownAccel(boolean input) {
        downAccel = input;
    }

    public int getPlayer() {
        return player;
    }
}
