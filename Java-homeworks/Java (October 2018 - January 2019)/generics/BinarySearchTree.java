package generics;

import java.util.Collection;

public class BinarySearchTree<E extends Comparable<? super E>> implements Collection<E> {
    private int numberOfNodes;
    private Node<E> root;

    private BinarySearchTree() {
        this.root = null;
        numberOfNodes = 0;
    }

    private BinarySearchTree(E e) {
        numberOfNodes = 1;
        this.root = new Node<>(e);
    }

    @Override
    public boolean add(E e) {
        if(root == null) {
            root = new Node<>(e);
            this.numberOfNodes++;
            return true;
        } else {
            Node<E> actualNode = root;
            Node<E> parent = null;

            while(actualNode != null) {
                parent = actualNode;
                if (actualNode.getE().compareTo(e) <= 0) {
                    actualNode = actualNode.getRight();
                } else {
                    actualNode = actualNode.getLeft();
                }
            }
            this.numberOfNodes++;
            actualNode = new Node<>(e);

            if(parent.getE().compareTo(e) <= 0) parent.setRight(actualNode);
            else parent.setLeft(actualNode);
            return true;
        }
    }

    @Override
    public BinaryIterator<E> iterator()  {
        return new BinaryIterator<>(this.root);
    }

    private int inOrder(Node<E> node, Object[] array, int counter) {
        if(node == null) return counter;

        counter = inOrder(node.getLeft(), array, counter);

        array[counter++] = node.getE();

        return inOrder(node.getRight(), array, counter);
    }

    @Override
    public Object[] toArray() {
        Object[] array = new Object[numberOfNodes];

        inOrder(this.root, array, 0);

        return array;
    }

    public int size() throws UnsupportedOperationException {
        throw new UnsupportedOperationException("size() is an unsupported operation");
    }

    public boolean isEmpty() throws UnsupportedOperationException {
        throw new UnsupportedOperationException("isEmpty() is an unsupported operation");
    }

    @Override
    public boolean contains(Object o) throws UnsupportedOperationException {
        throw new UnsupportedOperationException("contains(Object o) is an unsupported operation");
    }

    @Override
    public <T> T[] toArray(T[] a) throws UnsupportedOperationException {
        throw new UnsupportedOperationException("toArray(T[] a) is an unsupported operation");
    }

    @Override
    public boolean remove(Object o) throws UnsupportedOperationException {
        throw new UnsupportedOperationException("remove(Object o) is an unsupported operation");
    }

    @Override
    public boolean containsAll(Collection<?> c) throws UnsupportedOperationException {
        throw new UnsupportedOperationException("containsAll(Collection<?> c) is an unsupported operation");
    }

    @Override
    public boolean addAll(Collection<? extends E> c) throws UnsupportedOperationException {
        throw new UnsupportedOperationException("addAll(Collection<? extends E> c) is an unsupported operation");
    }

    @Override
    public boolean removeAll(Collection<?> c) throws UnsupportedOperationException {
        throw new UnsupportedOperationException("removeAll(Collection<?> c) is an unsupported operation");
    }

    @Override
    public boolean retainAll(Collection<?> c) throws UnsupportedOperationException {
        throw new UnsupportedOperationException("retainAll(Collection<?> c) is an unsupported operation");
    }

    @Override
    public void clear() throws UnsupportedOperationException {
        throw new UnsupportedOperationException("clear() is an unsupported operation");
    }

    public static void main(String[] args) {
        BinarySearchTree<OrderedPair<String, String>> bst = new BinarySearchTree<>(new OrderedPair<>("love", "java"));

        bst.add(new OrderedPair<>("java", "najlepsza"));
        bst.add(new OrderedPair<>("java 1", "good"));
        bst.add(new OrderedPair<>("j ava", "ekstra"));
        bst.add(new OrderedPair<>("bst", "to drzewo"));
        bst.add(new OrderedPair<>("java", "to kawa"));
        bst.add(new OrderedPair<>("heap", "hop"));
        bst.add(new OrderedPair<>("jak hip", "hop"));

        System.out.println("Wypisanie za pomocą iteratora");
        for(Object e: bst)
            System.out.println(e);

        System.out.println("===============");
        System.out.println("Wypisanie po przekonwertowaniu na tablice");

        Object[] array = bst.toArray();

        for(Object e: array)
            System.out.println(e);
    }
}