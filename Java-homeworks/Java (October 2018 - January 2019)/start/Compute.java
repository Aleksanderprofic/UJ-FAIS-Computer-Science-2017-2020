package start;

import java.util.function.*;

/**
 * Klasa implementująca metody plot(double, double, Computation), apply(double, Computation)
 * i fillArray(double[]) oraz wywołująca metodę main
 * @author Aleksander Profic
 */

public class Compute {

    //private static Multiplier object = new Multiplier(5);

    final static int n = 20;

    /**
     * metoda uruchamiana automatycznie
     * @param args nieużywany
     */
    public static void main(String[] args) {


        /* ->> Plot <<- */


        Computation<Double> f = new Multiplier(5);
        Multiplier g = new Multiplier(10);

        try {
            System.out.println("plot -> Instancja klasy Multiplier mnożąca x * 5, czyli klasa implementująca interfejs funkcyjny");
            plot(2.1, 3.3, f);
        } catch (DivideByZeroException e) {
            System.out.println(e.getMessage());
        }

        try {
            System.out.println("\nplot -> Obiekt klasy anonimowej mnożącej x * 5 implementujący interfejs funkcyjny ");
            plot(3.3, 2.1, new Computation<Double>() {
                @Override
                public Double compute(Double x) {
                    return x * 5;
                }
            });

        } catch(DivideByZeroException e) {
            System.out.println(e.getMessage());
        }

        try {
            System.out.println("\nplot -> Wyrazenie lambda mnozace x * 5");
            plot(2.1, 3.3, x -> {
                try {
                    Divide.div(x, 0);
                } catch(DivideByZeroException ex) {
                    System.out.println(ex.getMessage());
                } finally {
                    return x * 5;
                }
            });
        } catch(DivideByZeroException e) {
            System.out.println(e.getMessage());
        }

        try {
            System.out.println("\nplot -> Referencja do metody statycznej dodajacej 5+x");
            plot(2.1, 4.0, Multiplier::computeStatic);
        } catch(DivideByZeroException e) {
            System.out.println(e.getMessage());
        }


        System.out.println("\nplot -> Referencja do metody niestatycznej dzielącej a / x");
        try {
            plot(2.1, 3.3, g::compute2);
        } catch(DivideByZeroException e) {
            System.out.println(e.getMessage());
        }

        /* ->> Apply <<- */


        double[] array = new double[20];
        fillArray(array);

        System.out.println("\nBefore apply: ");
        for(double arr: array) {
            System.out.printf("%.4f\n", (arr));
        }

        try {
            apply(array, x -> x*3.2);
        } catch (DivideByZeroException e) {
            System.out.println(e.getMessage());
        }

        System.out.println("\nAfter apply: ");
        for(double arr: array) {
            System.out.printf("%.4f\n", (arr));
        }

        System.out.println("\n\n=====================\n");

        System.out.println(funkcja(g, Multiplier::compute3));
    }
    // Funkcja, która przyjmuje obiekt jakiejś klasy oraz referencje do niestatycznej metody w tej klasie, a nastepnie wywolac te metode na tym obiekcie

    private static Double funkcja(Multiplier obj, ToDoubleBiFunction<Multiplier, Double> f) {
        return f.applyAsDouble(obj, 8d);
    }

    /**
     * Wypełnia tablicę array losowymi wartościami: [0,1)*(i+1)
     * @param array tablica liczb zmiennoprzecinkowych podwójnej precyzji przekazana do wypełnienia
     */
    public static void fillArray(double[] array) throws NullPointerException {
        if(array == null) {
            throw new NullPointerException();
        }

        for(int i = 0; i < array.length; i++) {
            array[i] = Math.random()*(i+1);
        }
    }

    /**
     * Przyjmuje instancję interfejsu funkcyjnego Computation
     * i wypisuje n wartości zmiennej x (od xmin do xmax (włącznie) w równych odstępach)
     * oraz wartość zwracaną przez metodę compute dla argumentu x
     * W przypadku podania argumentów w złej kolejności (gdy xmax jest mniejsze od xmin) przyjmuje xmax jako xmin i na odwrót
     * @param xmin liczba zmiennoprzecinkowa podwójnej precyzji, od której zaczynamy wypisywanie
     * @param xmax liczba zmiennoprzecinkowa podwójnej precyzji, na której kończymy wypisywanie
     * @param f referencja do obiektu implementującego interfejs funkcyjny Computation
     */
    public static void plot(double xmin, double xmax, Computation<Double> f) throws DivideByZeroException {
        if(xmin < xmax) {
            double difference = (xmax - xmin)/(n-1);
            int i = 1;

            for(double d = xmin; d < xmax; d+=difference) {
                System.out.printf("%d\t-> %f: %f\n", i++, d, f.compute(d));
            }
            System.out.printf("%d\t-> %f: %f\n", i, xmax, f.compute(xmax));

        } else if (xmin == xmax) {
            System.out.println(xmin + ": " + f.compute(xmin));
        } else {
            /*
             * Traktuje argumenty w odwrotnej kolejności
             */
            System.out.println("I am smart enough to just swap arguments by myself :)");

            double difference = (xmin - xmax)/(n-1);
            int i = 1;

            for(double d = xmax; d < xmin; d+=difference) {
                System.out.printf("%d\t-> %f: %f\n", i++, d, f.compute(d));
            }
            System.out.printf("%d\t-> %f: %f\n", i, xmin, f.compute(xmin));

        }
    }

    /**
     * Wypełnia tablicę array wartościami funkcji f.compute(x),
     * gdzie x to kolejne oryginalne elementy tablicy array
     * @param array tablica liczb zmiennoprzecinkowych podwójnej precyzji
     * @param f referencja do obiektu implementującego interfejs funkcyjny Computation
     */
    public static void apply(double[] array, Computation<Double> f) throws NullPointerException, DivideByZeroException {
        if(array == null) {
            throw new NullPointerException();
        }
        for(int i = 0; i < array.length; i++) {
            array[i] = f.compute(array[i]);
        }
    }
}