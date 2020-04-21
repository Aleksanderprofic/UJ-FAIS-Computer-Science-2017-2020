#include <iostream>

unsigned long long int compare = 0;
unsigned long long int swap = 0;

void quickSort(int arr[], int left, int right) {
     int x = arr[(left + right) / 2];
     int l = left;
     int r = right;

     // zamieniamy elementy aby
     while(l < r) {
          //compare++;
          while(arr[l] < x) {
               //compare++;
               l++;
          }
          //compare++;
          while(arr[r] > x) {
               //compare++;
               r--;
          }
          //compare++;
          
          if(l <= r) {
               std::swap(arr[l++], arr[r--]);
               //swap += 3;
          }
          //compare++;
          
     }
     //compare++;
     if(left < r) quickSort(arr, left, r);
     //compare++;
     if(l < right) quickSort(arr, l, right);
     //compare++;
}

void printArray(int arr[], int n) {
     for(int i = 0; i < n; i++) {
          std::cout << arr[i] << std::endl;
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

     int arr[size];

     for(int i = 0; i < size; i++) {
          int numberEntered;
          std::cin >> numberEntered;
          arr[i] = numberEntered;
     }

     // std::cout << "Before sorting: " << std::endl;
     // printArray(arr, size);

     auto start = std::chrono::high_resolution_clock::now();
     quickSort(arr, 0, size-1/* compareswap */);
     auto end = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> difference = end - start;

     printf("recursive quick_sort time for %d elements: %f\n", size, difference.count());

     // std::cout << "After sorting: " << std::endl;
     //printArray(arr, size);


     //printf("Porownan: %llu\nZapisow: %llu\n", compare, swap);

     return 0;
}