package balls;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.io.IOException;

public class BallsFX extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("Playground.fxml"));
        primaryStage.setTitle("Balls");
        primaryStage.setScene(new Scene(root));
        primaryStage.setResizable(true);

        primaryStage.setOnCloseRequest(event -> System.exit(0));

        primaryStage.show();
    }
}
