#include <iostream>
#include <chrono>

void insertionSort(int array[], int n) {

     for(int i = 1; i < n; i++) {
          int j = i-1;

          int temp = array[i];

          while(j >= 0 && array[j] > temp) {
               array[j+1] = array[j];
               j--;
          }

          array[j+1] = temp;
     }
}

void printArray(int array[], int n) {

     for(int i = 0; i < n; i++) {
          std::cout << array[i] << std::endl;
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
          //std::cout << "Enter " << i+1 << " number: " << std::flush;
          std::cin >> numberEntered;
          array[i] = numberEntered;
     }

     //std::cout << "Before sorting: " << std::endl;
     //printArray(array, size);

     auto start = std::chrono::high_resolution_clock::now();
     insertionSort(array, size);
     auto end = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> difference = end - start;

     printf("insertion_sort time for %d elements: %f\n", size, difference.count());

     //std::cout << "After sorting: " << std::endl;
     //printArray(array, size);

     return 0;
}