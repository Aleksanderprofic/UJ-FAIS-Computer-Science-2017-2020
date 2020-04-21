
#include <iostream>


using namespace std;

void bubbleSort(int array[], int n) {
     int i, j;

     //cout << endl << "Sorting..." << endl;

     for(i = 0; i < n-1; i++) {
          for(j = 0; j < n-i-1; j++) {

               if(array[j] > array[j+1]) {
                    int temp;
                    temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;

                    //swap(array[j], array[j+1]);
               }
          }
     }
}

void printArray(int array[], int n) {

     for(int i = 0; i < n; i++) {
          cout << array[i] << endl;
     }
}

int main(int argc, char* argv[]) {

     int size;

     if(argc == 1) size = 10000;
     else if(argc == 2) {
          size = atoi(argv[1]);
     } else {
          std::cerr << "Too much arguments" << std::endl;
          return 1;
     }

     int array[size];

     for(int i = 0; i < size; i++) {
          int numberEntered;
          //cout << "Enter " << i+1 << " number: " << flush;
          cin >> numberEntered;
          array[i] = numberEntered;
     }

     //cout << "Before sorting: " << endl;
     //printArray(array, size);

     auto start = std::chrono::high_resolution_clock::now();
     bubbleSort(array, size);
     auto end = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> difference = end - start;

     printf("bubble_sort time for %d elements: %f\n", size, difference.count());

     

     //cout << "After sorting: " << endl;
     //printArray(array, size);

     return 0;
}