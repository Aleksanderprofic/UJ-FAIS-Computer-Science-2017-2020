package pongGameSwing;

import java.awt.*;

public class Ball {
    private double xSpeed, ySpeed, x, y;

    public Ball() {
        x = 350;
        y = 250;
        xSpeed = -2;
        ySpeed = 4;
    }

    public void draw(Graphics g) {
        g.setColor(Color.WHITE);

        // -10 ponieważ rysuje piłkę przyklejoną do punktu (x, y) od dołu z prawej strony
        g.fillOval((int)x-10, (int)y-10, 20, 20);
    }

    public void checkCollisionWithPaddle(Paddle p1, Paddle p2) {
        if(x == 50) {
            if(y >= p1.getY() && y <= p1.getY()+80) {
                xSpeed = -xSpeed;
            }
        } else if(x == 650){
            if(y >= p2.getY() && y <= p2.getY()+80) {
                xSpeed = -xSpeed;
            }
        }
    }

    public void move() {
        x += xSpeed;
        y += ySpeed;

        if(y < 10) ySpeed = -ySpeed;
        else if (y > 490) ySpeed = -ySpeed;
    }
    public int getX() {
        return (int)x;
    }

    public int getY() {
        return (int)y;
    }
}
