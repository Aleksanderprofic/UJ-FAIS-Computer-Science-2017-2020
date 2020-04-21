package mandelbrot;

import javafx.scene.image.PixelFormat;
import javafx.scene.image.PixelWriter;
import mandelbrot.complex.Complex;
import mandelbrot.complex.ComplexDrawable;

import java.awt.*;

public class MandelFractal implements ComplexDrawable {

    private double sqrR;

    /**
     * Konstruktor
     * @param r
     */
    MandelFractal(double r) {
        this.sqrR = r*r;
    }

    @Override
    public void draw(PixelWriter pw, Complex a, Complex b, int w, int h) {
        Complex p = new Complex();

        final double SCALERE = (b.re()-a.re())/w;
        final double SCALEIM = (b.im()-a.im())/h;

        int[] buffer = new int[w * h];

        for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++) {
                p.setRe(a.re() + SCALERE*x);
                p.setIm(a.im() + SCALEIM*y);

                buffer[w*y+x] = mandelbrot(p);
            }
        }

        pw.setPixels(0, 0, w, h, PixelFormat.getIntArgbInstance(), buffer, 0, w);
    }

    private int mandelbrot(Complex p) {
        Complex z = new Complex();
        int i = 0;

        for(; i < 100; i++) {
            z.mul(z);
            z.add(p);

            if(z.sqrAbs() >= sqrR) break;
        }

        if (i == 100) return 0xFF000000;
        else return Color.HSBtoRGB(i/100f, 0.850f, 1f);
    }
}