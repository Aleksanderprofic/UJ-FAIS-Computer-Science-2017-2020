package start;

/**
 * Interfejs funkcjonalny z zadeklarowaną funkcją compute
 */
@FunctionalInterface
public interface Computation<T> {
    T compute(T object) throws DivideByZeroException;
}
