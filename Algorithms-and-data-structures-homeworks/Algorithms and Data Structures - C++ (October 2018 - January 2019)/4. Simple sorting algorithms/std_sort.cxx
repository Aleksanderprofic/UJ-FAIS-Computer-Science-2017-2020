#include <iostream>
#include <chrono>

using namespace std;

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
     sort(array, array+size);
     auto end = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> difference = end - start;

     printf("std_sort time for %d elements: %f\n", size, difference.count());

     //cout << "After sorting: " << endl;
     //printArray(array, size);

     return 0;
}