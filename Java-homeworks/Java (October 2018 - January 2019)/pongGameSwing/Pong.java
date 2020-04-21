package pongGameSwing;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Pong extends JPanel implements Runnable {
    private int WIDTH, HEIGHT;
    private Paddle p1, p2;
    private Ball ball;
    private boolean isGameStarted;
    private boolean isGamePaused;

    public Pong(int WIDTH, int HEIGHT) {
        this.setSize(WIDTH, HEIGHT);
        this.WIDTH = WIDTH;
        this.HEIGHT = HEIGHT;

        this.isGameStarted = false;
        this.isGamePaused = false;

        p1 = new Paddle(1);
        p2 = new Paddle(2);
        ball = new Ball();


        this.setFocusable(true);

        this.addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent e) {

            }

            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_W) {
                    p1.setUpAccel(true);
                } else if (e.getKeyCode() == KeyEvent.VK_S) {
                    p1.setDownAccel(true);
                } else if (e.getKeyCode() == KeyEvent.VK_O) {
                    p2.setUpAccel(true);
                } else if (e.getKeyCode() == KeyEvent.VK_L) {
                    p2.setDownAccel(true);
                } else if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    isGameStarted = true;
                } else if (e.getKeyCode() == KeyEvent.VK_ESCAPE) {
                    isGamePaused = !isGamePaused;
                }
            }

            @Override
            public void keyReleased(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_W) {
                    p1.setUpAccel(false);
                } else if (e.getKeyCode() == KeyEvent.VK_S) {
                    p1.setDownAccel(false);
                } else if (e.getKeyCode() == KeyEvent.VK_O) {
                    p2.setUpAccel(false);
                } else if (e.getKeyCode() == KeyEvent.VK_L) {
                    p2.setDownAccel(false);
                }
            }
        });
    }

    public void paint(Graphics g) {
        g.setColor(Color.BLACK);
        g.fillRect(0, 0, WIDTH, HEIGHT);

        if (ball.getX() < -10 || ball.getX() > 710) {
            g.setColor(Color.RED);
            g.drawString("Game Over", 320, 250);
        } else {
            p1.draw(g);
            p2.draw(g);
            ball.draw(g);
        }

        if (isGameStarted) {
            if (isGamePaused) {
                g.setColor(Color.YELLOW);
                g.drawString("Game Paused", 304, 200);
                g.drawString("Press Escape to return", 279, 220);
            }
        } else {
            g.setColor(Color.YELLOW);
            g.drawString("PING PONG GAME", 296, 200);
            g.drawString("Press Enter to start", 291, 220);
        }
    }

    public void update(Graphics g) {
        paint(g);
    }

    @Override
    public void run() {
        while (true) {

            if (isGameStarted && !isGamePaused) {
                p1.move();
                p2.move();
                ball.move();
                ball.checkCollisionWithPaddle(p1, p2);
            }

            repaint();
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
