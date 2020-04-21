package start;

/**
 * Klasa obsługująca wyjątek dzielenia przez 0
 * @author Aleksander Profic
 */
public class DivideByZeroException extends java.lang.Exception {

    private String message;

    /**
     * Konstruktor zapisujący w zmiennej message komunikat o błędzie
     * @param a Dzielna
     * @param b Dzielnik
     */
    public DivideByZeroException(String a, String b) {
        message = "Second parameter is equal to 0. You can't divide " + a + " by " + b + "!";
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
