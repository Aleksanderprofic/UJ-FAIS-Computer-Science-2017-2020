package complexNumbers;

import org.junit.Assert;
import start.DivideByZeroException;

public class ComplexTest {

    public static void main(String[] args) {
        try{
            testMul();
            testStaticMul();
            testAdd();
            testStaticAdd();
            testSub();
            testStaticSub();
            testDiv();
            testStaticDiv();
            testAbs();
            testStaticAbs();
            testSqrAbs();
            testStaticSqrAbs();
            testPhase();
            testStaticPhase();

        } catch(NotAComplexNumberException e) {
            System.out.println(e.getMessage());
        } catch(DivideByZeroException e) {
            System.out.println(e.getMessage());
        } catch(IndefinitePhaseException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void testMul() throws NotAComplexNumberException {
        Complex a = new Complex("-1.2+3.4i");
        Complex b = Complex.valueOf("5.6-7.8i");
        a.mul(b);
        String result = a.toString();
        Assert.assertEquals("19.8+28.4i", result);
    }

    private static void testStaticMul() throws NotAComplexNumberException {
        Complex a = new Complex("-1.2+3.4i");
        Complex b = Complex.valueOf("5.6-7.8i");

        Complex c = Complex.mul(a, b);
        String result = c.toString();
        assert result.equals("19.8+28.4i");
    }

    private static void testAdd() throws NotAComplexNumberException {
        Complex a = new Complex("-1.2+3.4i");
        Complex b = Complex.valueOf("5.2-7.8i");

        a.add(b);
        String result = a.toString();
        Assert.assertEquals("4.0-4.4i", result);
    }

    private static void testStaticAdd() throws NotAComplexNumberException {
        Complex a = new Complex(-1.2,3.4);
        Complex b = Complex.valueOf("5.2-7.8i");

        Complex c = Complex.add(a, b);
        String result = c.toString();
        assert result.equals("4.0-4.4i");
    }

    private static void testSub() throws NotAComplexNumberException {
        Complex a = new Complex("-1.2+3.4i");
        Complex b = Complex.valueOf("5.2-7.8i");

        a.sub(b);
        String result = a.toString();
        Assert.assertEquals("-6.4+11.2i", result);
    }

    private static void testStaticSub() throws NotAComplexNumberException {
        Complex a = new Complex(-1.2,3.4);
        Complex b = Complex.valueOf("5.2-7.8i");

        Complex c = Complex.sub(a, b);
        String result = c.toString();
        assert result.equals("-6.4+11.2i");
    }

    private static void testDiv() throws NotAComplexNumberException, DivideByZeroException {
        Complex a = new Complex(1);
        a.setIm(8);
        Complex b = Complex.valueOf("2+3i");

        a.div(b);
        String result = a.toString();
        Assert.assertEquals("2.0+i", result);
    }

    private static void testStaticDiv() throws NotAComplexNumberException, DivideByZeroException {
        Complex a = new Complex();
        a.setRe(1);
        a.setIm(8);
        Complex b = Complex.valueOf("2+3i");
        Complex c = new Complex(0);

        Complex d = Complex.div(a,b);
        String result = d.toString();
        assert result.equals("2.0+i");

        //d = Complex.div(a,c);
    }

    private static void testAbs() {
        Complex a = new Complex(4,-3);


        String result = Double.toString(a.abs());
        Assert.assertEquals("5.0", result);
    }

    private static void testStaticAbs() throws NotAComplexNumberException {
        Complex a = new Complex("-3i-4");

        double result = Complex.abs(a);
        assert result == 5;
    }

    private static void testSqrAbs() {
        Complex a = new Complex();
        a.setVal(2,-2);

        double result = a.sqrAbs();
        Assert.assertEquals(8.0, result, 0.0005);
    }

    private static void testStaticSqrAbs() {
        Complex a = new Complex(-1,3);

        double result = Complex.sqrAbs(a);
        assert result == 10;
    }

    private static void testPhase() throws IndefinitePhaseException {
        Complex a = new Complex(1, 1);
        Complex b = new Complex();
        b.setVal(a);

        double result = b.phase();

        Assert.assertEquals(Math.PI/4, result, 0);
    }

    private static void testStaticPhase() throws NotAComplexNumberException, IndefinitePhaseException {
        Complex a = Complex.valueOf("-i");

        double result = Complex.phase(a);

        Assert.assertEquals(-(Math.PI/2), result, 0);
    }

}
