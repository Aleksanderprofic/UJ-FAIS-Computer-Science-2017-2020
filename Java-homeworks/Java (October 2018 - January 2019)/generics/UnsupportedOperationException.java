package generics;

public class UnsupportedOperationException extends RuntimeException {
    private String message;

    public UnsupportedOperationException(String message) {
        this.message = message;
    }

    public String getMessage() {
        return this.message;
    }
}
