package generics;


import java.util.Iterator;
import java.util.Stack;

public class BinaryIterator<E extends Comparable<? super E>> implements Iterator<E> {
    private Stack<Node<E>> stack;
    BinaryIterator(Node<E> root) {
        stack = new Stack<>();
        while (root != null) {
            stack.push(root);
            root = root.getLeft();
        }
    }

    @Override
    public boolean hasNext() {
        return !stack.isEmpty();
    }

    @Override
    public E next() {
        Node<E> node = stack.pop();
        E result = node.getE();
        if (node.getRight() != null) {
            node = node.getRight();
            while (node != null) {
                stack.push(node);
                node = node.getLeft();
            }
        }
        return result;
    }
}