package start;

/**
 * Klasa służąca do obliczania wyniku dzielenia dwóch liczb zmiennopozycyjnych podwójnej precyzji
 * @author Aleksander Profic
 */
public class Divide {

    /**
     * Metoda uruchamiana automatycznie
     * @param args Dwie liczby zmiennopozycyjne podwójnej precyzji
     * @throws DivideByZeroException Wyrzuca wyjątek przy dzieleniu przez 0
     */
    public static void main(String[] args) throws DivideByZeroException {
        if(args.length != 2) {
            System.out.println("Error. Enter 2 arguments which you want to divide");
            System.exit(0);
        }

        double a = 0, b = 0;

        try {
            a = Double.parseDouble(args[0]);
            b = Double.parseDouble(args[1]);
        } catch(NumberFormatException e) {
            System.out.println("Error. Needed 2 numbers instead of strings");
            System.exit(0);
        }

        System.out.println(args[0] + "/" + args[1] + " = " + div(a, b));
    }

    /**
     * Metoda obliczająca wynik dzielenia argumentu a przez b
     * @param a Liczba zmiennopozycyjna podwójnej precyzji, dzielna
     * @param b Liczba zmiennopozycyjna podwójnej precyzji, dzielnik
     * @return a/b
     * @throws DivideByZeroException Wyrzuca wyjątek przy dzieleniu przez 0
     */
    public static double div(double a, double b) throws DivideByZeroException {
        if(b==0) {
            throw new DivideByZeroException(Double.toString(a), Double.toString(b));
        } else {
            return a/b;
        }
    }
}
