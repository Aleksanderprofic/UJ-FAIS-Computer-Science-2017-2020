package mandelbrot.complex;

/**
 * Klasa obsługująca wyjątek konwersji Stringa na liczbę
 * @author Aleksander Profic
 */
public class NotAComplexNumberException extends Exception {
    private String message;

    /**
     * Konstruktor zapisujący w zmiennej message komunikat o błędzie
     * @param a String, który chcieliśmy przekonwertować
     */
    NotAComplexNumberException(String a) {
        if(a.isEmpty()) {
            message = "Its an empty string instead of a complex number";
        }
        message = a + " is not a complex number!";
    }

    /**
     * Metoda zwracająca komunikat o błędzie
     * @return message
     */
    @Override
    public String getMessage() {
        return message;
    }
}
