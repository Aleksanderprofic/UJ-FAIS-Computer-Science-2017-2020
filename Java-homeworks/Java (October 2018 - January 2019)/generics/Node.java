package generics;

public class Node<E extends Comparable<? super E>> {

    private E e;
    private Node<E> left;
    private Node<E> right;

    Node(E e) {
        this.e = e;
        this.left = this.right = null;
    }

    public E getE() {
        return this.e;
    }

    Node<E> getLeft() {
        return this.left;
    }

    Node<E> getRight() {
        return this.right;
    }

    public void setE(E e) {
        this.e = e;
    }

    void setLeft(Node<E> left) {
        this.left = left;
    }

    void setRight(Node<E> right) {
        this.right = right;
    }
}