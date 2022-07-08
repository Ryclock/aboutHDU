package atm.MyExceptions;

public class NoException extends Exception {

    public NoException() {
    }

    public NoException(String message) {
        super(message);
    }

    public NoException(Throwable cause) {
        super(cause);
    }

    public NoException(String message, Throwable cause) {
        super(message, cause);
    }

    public NoException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }


}
