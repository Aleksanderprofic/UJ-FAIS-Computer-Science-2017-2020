package serialize;

import java.io.*;
import java.lang.reflect.Array;
import java.util.Collection;
import java.util.Scanner;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

public class Circular<E extends Serializable> implements Serializable, BlockingQueue<E> {
    private int head, tail;
    private E[] buf;
    private static Scanner scanner = new Scanner(System.in);

    private Circular(int capacity) {
        this.buf = (E[]) new Serializable[capacity];
        this.head = 0;
        this.tail = 0;
    }

    @Override
    public boolean add(E e) {
        return offer(e);
    }

    @Override
    public boolean offer(E e) {
        if(size() == buf.length) return false;

        buf[tail++] = e;
        if(tail == buf.length) tail = 0;
        return true;
    }

    @Override
    public boolean offer(E e, long timeout, TimeUnit unit) throws InterruptedException {
        return false;
    }

    @Override
    public synchronized void put(E e) throws InterruptedException {
        if(size() == buf.length) this.wait();
        if(size() == 0) {
            offer(e);
            this.notify();
        } else offer(e);
    }

    @Override
    public E remove() {
        return poll();
    }

    @Override
    public boolean remove(Object o) {
        if(!isEmpty()) {
            int i = head, j;
            for(j = 0; j < size(); j++) {
                if(buf[i].equals(o)) break;
                i++;
            }
            if(j == size()) return false;



        }
        return false;
    }

    @Override
    public E poll() {
        if(isEmpty()) return null;

        E temp = buf[head];

        buf[head++] = null;
        if(head == buf.length) head = 0;
        return temp;
    }

    @Override
    public E poll(long timeout, TimeUnit unit) throws InterruptedException {
        return null;
    }

    @Override
    public synchronized E take() throws InterruptedException {
        E temp;
        if(isEmpty()) this.wait();
        if(buf.length == size()) {
            temp = poll();
            this.notify();
        } else temp = poll();

        return temp;
    }

    @Override
    public E element() {
        return null;
    }

    @Override
    public E peek() {
        return null;
    }

    @Override
    public int remainingCapacity() {
        return 0;
    }

    @Override
    public boolean containsAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean addAll(Collection<? extends E> c) {
        return false;
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        return false;
    }

    @Override
    public boolean retainAll(Collection<?> c) {
        return false;
    }

    @Override
    public void clear() {

    }

    @Override
    public int size() {
        if(isEmpty()) return 0;
        if(tail > head) return tail-head;
        return buf.length - (head-tail);
    }

    @Override
    public boolean isEmpty() {
        return buf[head] == null;
    }

    @Override
    public boolean contains(Object o) {
        return false;
    }

    @Override
    public CircularIterator<E> iterator() {
        return new CircularIterator<>(buf, head, tail);
    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }

    @Override
    public <T> T[] toArray(T[] array) {
        int size = size();
        // Jesli tablica jest za mala, alokuje nowa o tym samym typie
        if (array.length < size) array = (T[]) Array.newInstance(array.getClass().getComponentType(), size);
        // Jesli tablica jest za duza, ustawiam pierwszy wolny element na null
        else if (array.length > size) array[size] = null;

        int i = 0;
        for (E e: this) {
            array[i] = (T) e;
            i++;
        }
        return array;
    }

    @Override
    public int drainTo(Collection<? super E> c) {
        return 0;
    }

    @Override
    public int drainTo(Collection<? super E> c, int maxElements) {
        return 0;
    }

    private void writeObject(ObjectOutputStream out) throws IOException {

        int temp = head;
        out.writeInt(size());
        for(int i = 0; i < size(); i++) {
            out.writeObject(buf[temp++]);
            if(temp == buf.length) temp = 0;
        }
    }

    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
        int temp = in.readInt();
        this.buf = (E[]) new Serializable[temp];

        for(int i = 0; i < temp; i++) {
            buf[i] = (E) in.readObject();
        }
        this.head = 0;
        this.tail = buf.length;
    }

    @Override
    public String toString() {
        String returnObject = "";
        for(int i = 0; i < buf.length; i++) {
            returnObject = returnObject.concat("Index: " + i + "\nDistance from the head: " + Math.abs(head - i) +
                    "\nType of object: " + buf.getClass().getSimpleName() + "\nString: ");
            if(buf[i] == null) returnObject = returnObject.concat("Empty\n\n");
            else returnObject = returnObject.concat(buf[i].toString() + "\n\n");
        }
        return returnObject;
    }

    public static void main(String[] args) throws InterruptedException {
        final int N = 13;
        Circular<String> circular = new Circular<>(N);

        Thread thread = new Thread(() -> {
            for(int i = 0; i < N+2; i++) {
                try {
                    System.out.println("Enter:");
                    circular.put(scanner.nextLine());
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        Thread thread2 = new Thread(() -> {
            for(int i = 0; i < 5; i++) {
                try {
                    circular.take();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        thread2.start();
        thread.start();

        thread2.join();
        thread.join();
        System.out.println("Przed serializacją");
        for(String s: circular)
            System.out.println(s);
        //System.out.println(circular.toString());

        ObjectOutputStream out = null;
        try {
            out = new ObjectOutputStream(new FileOutputStream("Circular.ser"));
            out.writeObject(circular);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (out != null) {
            try {
                out.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        Circular<String> newObject = null;
        ObjectInputStream in = null;

        try {
            in = new ObjectInputStream(new FileInputStream("Circular.ser"));
            newObject = (Circular<String>) in.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }

        if (in != null) {
            try {
                in.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        System.out.println("Po serializacji");
        if (newObject != null) {
            for(String s: newObject)
                System.out.println(s);


            System.out.println("\nTO STRING METHOD\n");
            System.out.println(newObject.toString());
        }

        System.out.println("To Array ====");
        String[] array = new String[4];

        if (newObject != null) {
            array = newObject.toArray(array);
        }

        for(String s: array)
            System.out.println(s);
    }
}
