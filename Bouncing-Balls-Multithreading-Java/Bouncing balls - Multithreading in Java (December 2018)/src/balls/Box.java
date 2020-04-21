package balls;

import javafx.scene.shape.Rectangle;


class Box extends Rectangle {

    Box(double x, double y, double width, double height) {
        super(x, y, width, height);
    }
    void enter() {
        notify();
    }
}
