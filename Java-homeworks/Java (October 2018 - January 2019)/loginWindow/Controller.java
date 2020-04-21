package loginWindow;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.*;

public class Controller {

    private Stage stage;

    @FXML
    Label label;
    @FXML
    private TextField login;
    @FXML
    private TextField password;

    void setStage(Stage stage) {
        this.stage = stage;
    }

    public void login() throws IOException {
        InputStream is = this.getClass().getClassLoader().getResourceAsStream("data.txt");
        InputStreamReader isr = new InputStreamReader(is);

        BufferedReader br = new BufferedReader(isr);

        String readLine;

        boolean isLogin = false;

        while((readLine = br.readLine()) != null) {
            if(readLine.equals(login.getText())) {
                isLogin = true;
                break;
            }
            else br.readLine();
        }

        if(isLogin) {
            if((readLine = br.readLine()) != null) {
                if(!readLine.equals(password.getText())) {
                    label.setText("Zły login lub hasło!");
                    return;
                }
            }
            else {
                label.setText("Zły login lub hasło!");
                return;
            }
        } else {
            label.setText("Zły login lub hasło!");
            return;
        }

        changeSceneEnd();
    }

    private void changeSceneEnd() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("../loginWindow.EndScreen.fxml"));
            Parent root = loader.load();

            EndScreen endScreen = loader.getController();

            Scene scene = new Scene(root);

            stage.setScene(scene);

            //set stage
            endScreen.setStage(stage);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}