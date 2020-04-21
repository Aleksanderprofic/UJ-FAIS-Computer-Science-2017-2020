package serialize;

import java.util.Iterator;
import java.util.Stack;

public class CircularIterator<E> implements Iterator<E> {
    private Stack<E> stack;

    CircularIterator(E[] buf, int head, int tail) {
        stack = new Stack<>();
        tail--;
        if(tail < 0) tail = buf.length - 1;

        while(tail != head) {
            stack.push(buf[tail--]);
            if(tail < 0) tail = buf.length - 1;
        }
        stack.push(buf[head]);
    }

    @Override
    public boolean hasNext() {
        return !stack.isEmpty();
    }

    @Override
    public E next() {
        return stack.pop();
    }
}