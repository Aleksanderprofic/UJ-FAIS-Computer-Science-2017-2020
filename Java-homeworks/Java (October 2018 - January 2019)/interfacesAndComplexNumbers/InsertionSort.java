package complexNumbers;

public class InsertionSort implements ISort {

    /**
     * Sortuje tablicę, wykorzystując algorytm sortowania przez wstawianie
     * @param arr Tablica liczb zmiennoprzecinkowych podwójnej precyzji
     */
    public void sort(Double[] arr) {
        if(!ISort.sorted(arr)) {
            System.out.println("--->\tSortowanie przez wstawianie\t<---");
            for(int i = 1; i < arr.length; i++) {
                int j = i-1;

                double temp = arr[i];
                print2();
                while(j >= 0 && arr[j] > temp) {
                    arr[j+1] = arr[j];
                    j--;
                }

                arr[j+1] = temp;
            }
        } else {
            System.out.println("This array is already sorted");
        }
    }

    /*public void print() {
        System.out.println("PRINT z InsertionSort");
    }
*/
    public void printArray(Double[] arr) {
        System.out.print("[");
        for(int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
            if(i==arr.length-1) System.out.print("]");
            else System.out.print("|");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Double[] s = {1d, 2d, 3d, 4d, 5d};
        Double[] arr = {4.1, -2.5, 44.9, 13d, 11.1, 7.4, 987.1, 1.5, -5. };
        Double[] arr2 = {-4.1, 2.5, -44.9, -13d, -11.1, -7.4, -987.1, -1.5, 5. };

        InsertionSort is = new InsertionSort();

        System.out.println("Arr:");
        is.sort(arr);
        is.printArray(arr);

        System.out.println("Arr2:");
        is.sort(arr2);
        is.printArray(arr2);

        System.out.println("s:");
        is.sort(s);
        is.printArray(s);

    }
}
