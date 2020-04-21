#include <iostream>
#include <random>


std::random_device rd;
std::default_random_engine generator{rd()};

int inversionWithMergeSort(int tab[], int tmp[], int lewy, int prawy) {
     int srodek, i1, i2, i;
     int counter = 0;

     srodek = (lewy + prawy + 1) / 2;

     if (srodek - lewy > 1) {
          counter += inversionWithMergeSort(tab, tmp, lewy, srodek - 1);
     }
     
     if (prawy - srodek > 0) {
          counter += inversionWithMergeSort(tab, tmp, srodek, prawy);
     }
     
     i1 = lewy; i2 = srodek;

     // Merging
     for(i = lewy; i <= prawy; i++) {
          if(i1 == srodek) {
               tmp[i] = tab[i2++];
          } else if (i2 > prawy) {
               tmp[i] = tab[i1++];
          } else if(tab[i1] > tab[i2]) {
               counter += (srodek - i1);
               tmp[i] = tab[i2];
               i2++;
          } else 
               tmp[i] = tab[i1++];
     }
     
     for(i = lewy; i <= prawy; i++) {
          tab[i] = tmp[i];
     }
     return counter;
}


void knuthShuffle(int array[], int n) {
     for (int i = n - 1; i > 0; i--) {
          std::uniform_int_distribution<int> distribution(0, i);
          int j = distribution(generator);
          std::swap(array[i], array[j]);
     } 
}

int inversionBruteForce(int tab[], int n) {
     int counter = 0;

     for(int i = 0; i < n - 1; i++) {
          for(int j = i+1; j < n; j++) {
               if(tab[i] > tab[j]) counter++;
          }
     }

     return counter;
}

int main(int argc, char* argv[]) {
     if(argc < 2) {
          std::cerr << "Not enough arguments" << std::endl;
          exit(-1);
     }

     int n = atoi(argv[1]);

     int array[n];
     int temp[n];

     for(int i = 0; i < n; i++) {
          array[i] = i+1;
     }

     knuthShuffle(array, n);

     for(int i = 0; i < n; i++) {
          std::cout << array[i] << std::endl;
     }

     int countBruteForce = inversionBruteForce(array, n);
     std::cout << "Liczba inwersji brute force: " << countBruteForce << std::endl;

     int countMerge = inversionWithMergeSort(array, temp, 0, n - 1);
     std::cout << "Liczba inwersji merge: " << countMerge << std::endl;
}