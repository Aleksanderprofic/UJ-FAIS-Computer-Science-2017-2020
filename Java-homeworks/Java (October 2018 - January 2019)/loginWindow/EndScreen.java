package loginWindow;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class EndScreen {

    private Stage stage;
    @FXML
    Button button;

    public void changeSceneStart() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("../Controller.fxml"));
            Parent root = loader.load();

            Controller controller = loader.getController();

            Scene scene = new Scene(root);

            stage.setScene(scene);

            //set stage
            controller.setStage(stage);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    void setStage(Stage stage) {
        this.stage = stage;
    }
}
