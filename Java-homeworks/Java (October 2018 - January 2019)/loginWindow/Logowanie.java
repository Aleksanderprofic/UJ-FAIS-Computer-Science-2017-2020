package loginWindow;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Logowanie extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {

        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("Controller.fxml"));
            Parent root = loader.load();

            primaryStage.setTitle("Logowanie");
            primaryStage.setScene(new Scene(root));
            primaryStage.setResizable(false);
            primaryStage.show();

            Controller controller = loader.getController();

            //set stage
            controller.setStage(primaryStage);
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}