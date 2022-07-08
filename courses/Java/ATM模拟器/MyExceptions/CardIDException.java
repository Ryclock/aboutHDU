package atm.MyExceptions;

public class CardIDException extends Exception {

    public CardIDException() {
    }

    public CardIDException(String message) {
        super(message);
    }

    public CardIDException(Throwable cause) {
        super(cause);
    }

    public CardIDException(String message, Throwable cause) {
        super(message, cause);
    }

    public CardIDException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }

}
