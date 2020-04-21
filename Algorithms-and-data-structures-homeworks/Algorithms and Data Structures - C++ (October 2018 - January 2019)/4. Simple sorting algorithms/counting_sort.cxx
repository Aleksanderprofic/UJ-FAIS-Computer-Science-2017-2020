#include <iostream>

void countingSort(int T[], int size, int max, int min) {
     int compartment = max-min+1;
     int Tpom[compartment];

     for(int i = 0; i < compartment; i++) {
          Tpom[i] = 0;
     }

     for(int i = 0; i < size; i++) {
          ++Tpom[T[i]-min];
     }

     int j = 0, i = 0;

     while(i < size) {
          while(Tpom[j] > 0) {
               T[i++] = j+min;
               Tpom[j]--;
          }
          j++;
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

     int min, max;

     int T[size];


     for(int i = 0; i < size; i++) {
          int numberEntered;
          //std::cout << "Enter " << i+1 << " number: " << std::flush;
          std::cin >> numberEntered;
          T[i] = numberEntered;

          if(i == 0) {
               min = numberEntered;
               max = numberEntered;
          } else {
               if(numberEntered < min) min = numberEntered;
               else if(numberEntered > max) max = numberEntered;
          }
     }

     //printArray(T, size);

     auto start = std::chrono::high_resolution_clock::now();
     countingSort(T, size, max, min);
     auto end = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> difference = end - start;

     printf("counting_sort time for %d elements: %f\n", size, difference.count());

     //printArray(T, size);

     return 0;
}