#include <iostream>

unsigned long long int compareMin = 0;
unsigned long long int compareMax = 0;
unsigned long long int swap = 0;

void MergeSort(int tab[], int tmp[], int lewy, int prawy) {
     int srodek, i1, i2, i;

     srodek = (lewy + prawy + 1) / 2;

     if (srodek - lewy > 1) {
          MergeSort(tab, tmp, lewy, srodek - 1);
     }
     //compareMin++;
     //compareMax++;
     if (prawy - srodek > 0) {
          MergeSort(tab, tmp, srodek, prawy);
     }
     //compareMin++;
     //compareMax++;

     i1 = lewy; i2 = srodek;

     // Merging
     for(i = lewy; i <= prawy; i++) {
          //compareMin++;
          //compareMax++;
          
          //compareMin++;
          //compareMax += 3;
          //swap++;
          tmp[i] = ((i1 == srodek) || 
               ((i2 <= prawy) && (tab[i1] > tab[i2]))) ? tab[i2++] : tab[i1++];
     }
     //compareMin++;
     //compareMax++;

     for(i = lewy; i <= prawy; i++) {
          //compareMin++;
          //compareMax++;
          //swap++;
          tab[i] = tmp[i];
     }
     //compareMin++;
     //compareMax++;
}

void printArray(int arr[], int n) {
     for(int i = 0; i < n; i++) {
          std::cout << arr[i] << std::endl;
     }
}

int main(int argc, char* argv[]) {
     if(argc < 2) {
          std::cerr << "Not enough arguments" << std::endl; 
          exit(-1);
     }

     const int N = atoi(argv[1]);

     int i;
     int tab[N], tmp[N];
     

     for(i = 0; i < N; i++) {
          std::cin >> tab[i];
     }
     auto start = std::chrono::high_resolution_clock::now();

     MergeSort(tab, tmp, 0, N-1);

     auto end = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> difference = end - start;
     //printf("recursive merge sort time for %d elements: %f\n", N, difference.count());

     printArray(tab, N);
     
     //printf("Porownan min: %llu\nPorownan max: %llu\nZapisow: %llu\n", compareMin, compareMax, swap);

     return 0;
} 