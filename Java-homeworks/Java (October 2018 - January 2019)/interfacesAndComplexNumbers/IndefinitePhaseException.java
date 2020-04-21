package complexNumbers;

public class IndefinitePhaseException extends java.lang.Exception {

    private String message;

    /**
     * Konstruktor zapisujący w zmiennej message komunikat o błędzie
     *
     * @param complexNumber Liczba zespolona
     */
    public IndefinitePhaseException(String complexNumber) {
        message = "Can't specify the phase of complex number:  " + complexNumber + " !";
    }

    /**
     * Metoda zwracająca komunikat o błędzie
     *
     * @return message
     */
    @Override
    public String getMessage() {
        return message;
    }
}
