package complexNumbers;

/**
 * Interfejs do implementacji sortowania -> domyślne sortowanie bąbelkowe
 */
public interface ISort {
    /**
     * Sortuje tablicę, wykorzystując algorytm sortowania bąbelkowego
     * @param arr Tablica liczb zmiennoprzecinkowych podwójnej precyzji
     */
    default void sort(Double[] arr) {
        if(!sorted(arr)) {
            System.out.println("--->\tSortowanie bąbelkowe\t<---");
            for(int i = 0; i < arr.length-1; i++) {
                for(int j = 0; j < arr.length-i-1; j++) {
                    if(arr[j] > arr[j+1]) {
                        double temp;
                        temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;
                    }
                }
            }
        } else System.out.println("Already sorted");
    }

    default void print() {
        System.out.println("PRINT z ISort");
    }

    default void print2() {
        print();
    }
    /**
     * Sprawdza czy tablica jest posortowana
     * @param arr Tablica liczb zmiennoprzecinkowych podwójnej precyzji
     * @return True - jeśli tablica jest posortowana, false - jeśli nie jest posortowana
     */
    static boolean sorted(Double[] arr) {
        for(int i = 1; i < arr.length; i++) {
            if(arr[i-1] > arr[i]) return false;
        }
        return true;
    }
}
