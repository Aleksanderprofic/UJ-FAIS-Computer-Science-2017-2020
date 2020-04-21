package generics;

import java.util.*;

public class Collections {
    private static final int N;
    private static final Integer random[][];
    private static final Integer sorted[][];
    private static final Integer sorted2[][];


    static {
        N  = 100000;
        random = new Integer[][]{new Integer[N], new Integer[N], new Integer[N]};
        sorted = new Integer[][]{new Integer[N], new Integer[N], new Integer[N]};
        sorted2 = new Integer[][]{new Integer[N], new Integer[N], new Integer[N]};

        for(int i = 0; i < N; i++) {
            random[0][i] = (int)(Math.random() * N);
            sorted[0] = random[0];
            sorted2[0] = random[0];
        }
        System.out.println("ADD ARRAY initialized");

        for(int i = 0; i < N; i++) {
            random[1][i] = (int)(Math.random() * N);
            sorted[1] = random[1];
            sorted2[1] = random[1];
        }
        System.out.println("SEARCH ARRAY initialized");

        for(int i = 0; i < N; i++) {
            random[2][i] = (int)(Math.random() * N);
            sorted[2] = random[2];
            sorted2[2] = random[2];
        }
        System.out.println("REMOVE ARRAY initialized");
    }
    public static void main(String[] args) {

        ArrayList<AbstractCollection<Integer>> al = new ArrayList<>(7);

        al.add(new ArrayList<>());
        al.add(new HashSet<>());
        al.add(new LinkedList<>());
        al.add(new Stack<>());
        al.add(new Vector<>());
        al.add(new PriorityQueue<>());
        al.add(new TreeSet<>());

        // TESTING BYTES
/*
        System.out.println("Bytes of one Integer: " + MyAgent.getObjectSize(5));

        arrayList.add(5);
        arrayList.add(10);
        arrayList.add(555);
        System.out.println("Bytes of one element in ArrayList: " + MyAgent.getObjectSize(arrayList.get(2)));
        arrayList.clear();
        hashSet.add(5);
        System.out.println("Bytes of one element in HashSet: " + MyAgent.getObjectSize(hashSet.toArray()[0]));
        hashSet.clear();
        linkedList.add(5);
        System.out.println("Bytes of one element in LinkedList: " + MyAgent.getObjectSize(linkedList.get(0)));
        linkedList.clear();
        stack.add(5);
        System.out.println("Bytes of one element in Stack: " + MyAgent.getObjectSize(stack.get(0)));
        stack.clear();
        vector.add(5);
        System.out.println("Bytes of one element in Vector: " + MyAgent.getObjectSize(vector.get(0)));
        vector.clear();
        priorityQueue.add(5);
        System.out.println("Bytes of one element in PriorityQueue: " + MyAgent.getObjectSize(priorityQueue.toArray()[0]));
        priorityQueue.clear();
        treeSet.add(5);
        System.out.println("Bytes of one element in TreeSet: " + MyAgent.getObjectSize(treeSet.toArray()[0]));
        treeSet.clear();

*/
        // END OF TESTING BYTES

        Arrays.sort(sorted[0]);
        Arrays.sort(sorted2[0], java.util.Collections.reverseOrder());
        Arrays.sort(sorted[1]);
        Arrays.sort(sorted2[1], java.util.Collections.reverseOrder());
        Arrays.sort(sorted[2]);
        Arrays.sort(sorted2[2], java.util.Collections.reverseOrder());


        for(int i = 0; i < 7; i++) {
            double[] addTimes = new double[3];
            double[] contTimes = new double[3];
            double[] remTimes = new double[3];
            double[] table;
            table = checkTime(al.get(i), 1);
            addTimes[0] = table[0];
            contTimes[0] = table[1];
            remTimes[0] = table[2];
            al.get(i).clear();

            table = checkTime(al.get(i), 2);
            addTimes[1] = table[0];
            contTimes[1] = table[1];
            remTimes[1] = table[2];
            al.get(i).clear();

            table = checkTime(al.get(i), 3);
            addTimes[2] = table[0];
            contTimes[2] = table[1];
            remTimes[2] = table[2];
            al.get(i).clear();

            System.out.printf("\nŚredni czas operacji add() -> %.7f\n", ex(addTimes));
            System.out.printf("Odchylenie standardowe operacji add() -> %.5f\n\n", sigma(addTimes));

            System.out.printf("Średni czas operacji contains() -> %.7f\n", ex(contTimes));
            System.out.printf("Odchylenie standardowe operacji contains() -> %.5f\n\n", sigma(contTimes));

            System.out.printf("Średni czas operacji remove() -> %.7f\n", ex(remTimes));
            System.out.printf("Odchylenie standardowe operacji remove() -> %.5f\n\n", sigma(remTimes));
        }
    }

    private static double ex(double[] arr) {
        double ex = 0;
        for (double anArr : arr) {
            ex += anArr;
        }
        ex /= arr.length;

        return ex;
    }

    private static double sigma(double[] arr) {
        double ex, sigma = 0;

        ex = ex(arr);

        for (double anArr : arr) {
            sigma += Math.pow(anArr - ex, 2);
        }
        sigma = Math.sqrt(sigma/arr.length);

        return sigma;
    }

    private static double[] checkTime(AbstractCollection<Integer> abstractCollection, int whichTable) {

        String name = abstractCollection.getClass().getTypeName();
        double[] table = new double[3];

        switch(whichTable) {
            case 1:
                table[0] = addTime(abstractCollection, 1);
                System.out.printf(name + " add() on " + N + " random el: %.7fs\n", table[0]);

                table[1] = containsTime(abstractCollection, 1);
                System.out.printf(name + " contains() on " + N + " random el: %.7fs\n", table[1]);

                table[2] = removeTime(abstractCollection, 1);
                System.out.printf(name + " remove() on " + N + " random el: %.7fs\n", table[2]);

                return table;
            case 2:
                table[0] = addTime(abstractCollection, 2);
                System.out.printf(name + " add() on " + N + " sorted el: %.7fs\n", table[0]);

                table[1] = containsTime(abstractCollection, 2);
                System.out.printf(name + " contains() on " + N + " sorted el: %.7fs\n", table[1]);

                table[2] = removeTime(abstractCollection, 2);
                System.out.printf(name + " remove() on " + N + " sorted el: %.7fs\n", table[2]);

                return table;
            case 3:
                table[0] = addTime(abstractCollection, 3);
                System.out.printf(name + " add() on " + N + " rev sorted el: %.7fs\n", table[0]);

                table[1] = containsTime(abstractCollection, 3);
                System.out.printf(name + " contains() on " + N + " rev sorted el: %.7fs\n", table[1]);

                table[2] = removeTime(abstractCollection, 3);
                System.out.printf(name + " remove() on " + N + " rev sorted el: %.7fs\n", table[2]);
                abstractCollection.clear();
                return table;
            default:
                return null;
        }
    }

    private static double addTime(AbstractCollection<Integer> abstractCollection, int whichTable) {
        long start;

        switch (whichTable) {
            case 1:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.add(random[0][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;
            case 2:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.add(sorted[0][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;
            case 3:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.add(sorted2[0][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;
            default:
                return 0;
        }
    }

    private static double containsTime(AbstractCollection<Integer> abstractCollection, int whichTable) {

        long start;

        switch (whichTable) {
            case 1:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.contains(random[1][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;
            case 2:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.contains(sorted[1][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;
            case 3:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.contains(sorted2[1][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;

            default:
                return 0;

        }
    }

    private static double removeTime(AbstractCollection<Integer> abstractCollection, int whichTable) {

        long start;

        switch (whichTable) {
            case 1:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.remove(random[2][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;
            case 2:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.remove(sorted[2][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;
            case 3:
                start = System.currentTimeMillis();
                for(int i = 0; i < N; i++) {
                    abstractCollection.remove(sorted2[2][i]);
                }
                return (System.currentTimeMillis() - start)/1000.0;

            default:
                return 0;

        }
    }
}