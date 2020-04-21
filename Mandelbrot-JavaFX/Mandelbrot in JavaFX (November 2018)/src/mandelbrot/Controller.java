package mandelbrot;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.effect.BlendMode;
import javafx.scene.image.PixelWriter;
import javafx.scene.image.WritableImage;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import mandelbrot.complex.Complex;

public class Controller {
    public Label label;											// Etykieta
    public Canvas canvas, canvas2;								// "Płótno" do rysowania
    private GraphicsContext gc, gc2;							// Kontekst graficzny do "płótna"
    private double x1, y1, x2, y2;                      // Współrzędne ramki
    private int WIDTH;
    private int HEIGHT;
    private double r;
    private Complex a;
    private Complex b;
    private Complex zA;
    private Complex zB;
    private boolean mandel;
    private boolean canMandel;

    @FXML
    private TextField parR;
    @FXML
    private TextField w;
    @FXML
    private TextField h;
    @FXML
    private TextField firstR;
    @FXML
    private TextField secondR;
    @FXML
    private TextField firstI;
    @FXML
    private TextField secondI;

    public Controller() {
        mandel = false;
        canMandel = false;
        a = new Complex(-2, 2);
        b = new Complex(1.5, -1.8);
        zA = new Complex(a);
        zB = new Complex(b);
        r = 2d;
        WIDTH = 512;
        HEIGHT = 512;
    }

    public void mandel() {
        mandel = !mandel;
    }

    public void sayHello(ActionEvent actionEvent) {
        label.setText("Hello");
    }

    public void initialize() {
        gc = canvas.getGraphicsContext2D();
        gc2 = canvas2.getGraphicsContext2D();
        clear(gc);
        clear(gc2);
    }

    private void clear(GraphicsContext gc) {
        gc.setFill(Color.WHITE);
        gc.setGlobalBlendMode(BlendMode.SRC_OVER);
        if(mandel) gc.fillRect(0, 0, canvas2.getWidth(), canvas2.getHeight());
        else gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
    }

    private void rect(GraphicsContext gc) {						// Metoda rysuje prostokąt o rogach (x1, y1) i (x2, y2)
        double x = x1;
        double y = y1;
        double w = x2 - x1;
        double h = y2 - y1;

        if (w < 0) {
            x = x2;
            w = -w;
        }

        if (h < 0) {
            y = y2;
            h = -h;
        }

        gc.strokeRect(x + 0.5, y + 0.5, w, h);
    }

    public void mouseMoves(MouseEvent mouseEvent) {
        double x = mouseEvent.getX();
        double y = mouseEvent.getY();

        if(mandel) {
            gc2.setGlobalBlendMode(BlendMode.DIFFERENCE);
            gc2.setStroke(Color.WHITE);
            rect(gc2);
            x2 = x;
            y2 = y;
            rect(gc2);
        } else {
            gc.setGlobalBlendMode(BlendMode.DIFFERENCE);
            gc.setStroke(Color.WHITE);
            rect(gc);
            x2 = x;
            y2 = y;
            rect(gc);
        }
    }

    public void drawRect(ActionEvent actionEvent) {
        gc.setStroke(Color.web("#FFF0F0"));
        gc.setGlobalBlendMode(BlendMode.MULTIPLY);
        gc.strokeRect(100.5, 100.5, 200, 200);
    }

    public void mousePressed(MouseEvent mouseEvent) {
        x1 = mouseEvent.getX();
        y1 = mouseEvent.getY();
        x2 = x1;
        y2 = y1;
    }

    public void mouseReleased(MouseEvent mouseEvent) {
        if(mandel) rect(gc2);
        else rect(gc);

        System.out.printf("%f %f %f %f\n", x1, y1, x2, y2);
        if(x1 > x2) {
            double temp = x1;
            x1 = x2;
            x2 = temp;
        }

        if(y1 > y2) {
            double temp = y1;
            y1 = y2;
            y2 = temp;
        }

        if(mandel && canMandel) {
            scaleComplex();
            drawMandelbrot();
        }
    }

    public void clearCanvas(ActionEvent actionEvent) {
        clear(gc);
    }

    public void clearCanvas2(ActionEvent actionEvent) {
        clear(gc2);
        canMandel = false;
        restoreDefaultValues();
    }

    public void draw(ActionEvent actionEvent) {
        final int size = 512;
        WritableImage wr = new WritableImage(size, size);
        PixelWriter pw = wr.getPixelWriter();

        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                pw.setArgb(x, y, (x & y) == 0 ? 0xFFFF00FF : 0xFFFFFFFF);	// Rysuje trójkąt Sierpińskiego
            }
        }

        gc.setGlobalBlendMode(BlendMode.SRC_OVER);
        gc.drawImage(wr, 0, 0, 512, 512);
    }

    public void drawMandelbrot() {
        clear(gc2);

        canMandel = true;
        MandelFractal mf = new MandelFractal(r);
        WritableImage wi = new WritableImage(WIDTH, HEIGHT);
        PixelWriter pw = wi.getPixelWriter();

        mf.draw(pw, zA, zB, WIDTH, HEIGHT);

        gc2.setGlobalBlendMode(BlendMode.SRC_OVER);
        gc2.drawImage(wi, 0, 0, WIDTH, HEIGHT);
    }

    private void scaleComplex() {
        final double RSCALE = (zB.re()- zA.re())/WIDTH;
        final double ISCALE = (zB.im()- zA.im())/HEIGHT;

        double newRe1 = zA.re() + (RSCALE)*x1;
        double newIm1 = zA.im() + (ISCALE)*y1;
        double newRe2 = zB.re() - (RSCALE)*(WIDTH - x2);
        double newIm2 = zB.im() - (ISCALE)*(HEIGHT - y2);

        zA.setRe(newRe1);
        zA.setIm(newIm1);
        zB.setRe(newRe2);
        zB.setIm(newIm2);

        firstR.textProperty().setValue(Double.toString(newRe1));
        firstI.textProperty().setValue(Double.toString(newIm1));
        secondR.textProperty().setValue(Double.toString(newRe2));
        secondI.textProperty().setValue(Double.toString(newIm2));
    }

    public void setFirstR() {
        try {
            this.a.setRe(Double.parseDouble(firstR.textProperty().getValue()));
            this.zA.setRe(a.re());
        } catch(NumberFormatException e) {
            System.out.println("Enter a valid number");
        }
    }

    public void setFirstI() {
        try {
            this.a.setIm(Double.parseDouble(firstI.textProperty().getValue()));
            this.zA.setIm(a.im());
        } catch(NumberFormatException e) {
            System.out.println("Enter a valid number");
        }
    }

    public void setSecondR() {
        try {
            this.b.setRe(Double.parseDouble(secondR.textProperty().getValue()));
            this.zB.setRe(b.re());
        } catch(NumberFormatException e) {
            System.out.println("Enter a valid number");
        }
    }

    public void setSecondI() {
        try {
            this.b.setIm(Double.parseDouble(secondI.textProperty().getValue()));
            this.zB.setIm(b.im());
        } catch(NumberFormatException e) {
            System.out.println("Enter a valid number");
        }
    }

    public void setWIDTH() {
        try {
            int temp;
            if((temp = Integer.parseInt(w.getText())) > 512) {
                System.out.println("Too big WIDTH");
                this.WIDTH = 512;
                w.textProperty().setValue("512");
            }
            else this.WIDTH = temp;
        } catch(NumberFormatException e) {
            System.out.println("Enter a valid number");
        }
    }

    public void setHEIGHT() {
        try {
            int temp;
            if((temp = Integer.parseInt(h.getText())) > 512) {
                System.out.println("Too big HEIGHT");
                this.HEIGHT = 512;
                h.textProperty().setValue("512");
            }
            else this.HEIGHT = temp;
        } catch(NumberFormatException e){
            System.out.println("Enter a valid number");
        }
    }

    public void setR() {
        try {
            this.r = Double.parseDouble(parR.getText());
        } catch(NumberFormatException e){
            System.out.println("Enter a valid number");
        }
    }

    private void restoreDefaultValues() {
        this.r = 2d;
        this.WIDTH = 512;
        this.HEIGHT = 512;
        this.a.setVal(-2.0, 2.0);
        this.b.setVal(1.5, -1.8);
        this.zA.setVal(a);
        this.zB.setVal(b);
        canvas2.setWidth(512d);
        canvas2.setHeight(512d);

        parR.textProperty().setValue("2.0");
        w.textProperty().setValue("512");
        h.textProperty().setValue("512");
        firstR.textProperty().setValue("-2.0");
        firstI.textProperty().setValue("2.0");
        secondR.textProperty().setValue("1.5");
        secondI.textProperty().setValue("-1.8");
    }
}