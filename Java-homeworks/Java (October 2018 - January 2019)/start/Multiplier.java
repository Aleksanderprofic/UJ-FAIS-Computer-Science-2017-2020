package start;

/**
 * Klasa implementująca interfejs funkcyjny Computation,
 * implementuje metody służące do mnożenia liczb zmiennoprzecinkowych przez wartość zmiennej zdefiniowanej w tej klasie
 * @author Aleksander Profic
 */
public class Multiplier implements Computation<Double> {
    /**
     * Zmienna prywatna, przez którą mnożymy liczby podane w argumencie metod compute i computeStatic
     */
    private double a;

    /**
     * Konstruktor inicjalizujący wartość zmiennej statycznej 'a'
     * @param a liczba zmiennoprzecinkowa podwójnej precyzji
     */
    public Multiplier(double a) {
        this.a = a;
    }

    /**
     * Mnoży wartość a przez podaną jako parametr wartość x
     * @param x liczba zmiennoprzecinkowa podwójnej precyzji
     * @return a*x
     */
    public Double compute(Double x) {
        return a*x;
    }

    /**
     * Dzieli wartość a przez podaną jako parametr wartość x
     * @param x liczba zmiennoprzecinkowa podwójnej precyzji
     * @return a/x
     * @throws DivideByZeroException
     */
    public Double compute2(Double x) throws DivideByZeroException {
        if(x == 0) {
            throw new DivideByZeroException(Double.toString(a), Double.toString(x));
        }
        return a/x;
    }

    public Double compute3(Double x) {
        return a*x;
    }

    /**
     * Statyczny odpowiednik metody niestatycznej compute: mnoży wartość a przez podaną jako parametr wartość x
     * @param x liczba zmiennoprzecinkowa podwójnej precyzji
     * @return 5+x
     */
    public static Double computeStatic(Double x) {
        return 5+x;
    }
}
