package pongGameSwing;

import javax.swing.*;
import java.awt.*;

public class Main {
    public static void main(String[] args) {
        //Create  a new window and display the game
        JFrame frame = new JFrame("Game");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());
        frame.setSize(700, 520);
        // Okienko pojawia się na środku a nie w lewym górmym rogu
        frame.setLocationRelativeTo(null);
        Pong game = new Pong(700,500);
        frame.add(game, BorderLayout.CENTER);

        Thread pongGame = new Thread(game);

        pongGame.start();

        frame.setVisible(true);
    }
}
