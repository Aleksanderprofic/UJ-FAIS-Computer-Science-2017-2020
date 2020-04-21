#include <iostream>
#include <cstdio>

void selectionSort(int T[], int n) {
     int* pMin;
     int temp;

     for(int i = 0; i < n-1; i++) {
          pMin = &T[i];
          for(int j = i+1; j < n; j++) { 
               if(*pMin > T[j]) { 
                    pMin = &T[j];
               }
          }
          temp = T[i];
          T[i] = *pMin;
          *pMin = temp;
     }
}

void printArray(int T[], int n) {

     for(int i = 0; i < n; i++) {
          std::cout << T[i] << std::endl;
     }
}

int main(int argc, char* argv[]) {

     //std::ios_base::sync_with_stdio(false);

     int size;

     if(argc == 1) size = 10000;
     else if(argc == 2) {
          size = atoi(argv[1]);
     } else {
          std::cerr << "Too much arguments" << std::endl;
          return 1;
     }

     int T[size];


     for(int i = 0; i < size; i++) {
          int numberEntered;
          //std::cout << "Enter " << i+1 << " number: " << std::flush;
          std::cin >> numberEntered;
          T[i] = numberEntered;
     }

     //printArray(T, size);

     auto start = std::chrono::high_resolution_clock::now();
     selectionSort(T, size);
     auto end = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> difference = end - start;

     printf("selection_sort time for %d elements: %f\n", size, difference.count());
     
     //printArray(T, size);

     return 0;
}