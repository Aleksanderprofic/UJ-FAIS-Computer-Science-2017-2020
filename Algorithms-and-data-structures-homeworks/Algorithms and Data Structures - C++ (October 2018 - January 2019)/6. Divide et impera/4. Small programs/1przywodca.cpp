#include <iostream>

// Zakładamy, ze istnieje
int przywodca(int tab[], int n) {
     int counter = 0;
     int lider;
     for (int i = 0; i < n; i++) {
          if(counter == 0) {
               counter++;
               lider = i;
          } else if (tab[i] == tab[lider]) counter++;
          else counter--;
     }
     return tab[lider];
}

// sprawdzenie czy istnieje
int przywodca2(int tab[], int n) {
     int counter = 0;
     int lider;
     for (int i = 0; i < n; i++) {
          if(counter == 0) {
               counter++;
               lider = i;
          } else if (tab[i] == tab[lider]) counter++;
          else counter--;
     }

     if(counter > 0) {
          counter = 0;
          for (int i = 0; i < n; i++) {
               if(tab[lider] == tab[i]) counter++;
          }
          if(counter > n/2) return tab[lider];
          else return -1;
     } else return -1;
}

int main() {
     int temp;

     int tab1[10] = {10, 10, 10, 10, 10, 10, 2, 1, 3, 6};
     int tab2[10] = {5, 2, 5, 5, 5, 2, 1, 1, 5, 5};
     int tab3[10] = {5, 2, 5, 0, 1, 2, 1, 1, 1, 10};

     int* tab[] = { tab1, tab2, tab3 };

     std::cout << "Przywodca1: " << przywodca(tab1, 10) << std::endl;
     
     for(int i = 0; i < 3; i++) {
          if((temp = przywodca2(tab[i], 10)) == -1) 
               std::cout << "Przywodca w tablicy " << (i+1) << " nie istnieje" << std::endl;
          else std::cout << "Przywodca w tablicy " << (i+1) << ": " << temp << std::endl;
     }
}