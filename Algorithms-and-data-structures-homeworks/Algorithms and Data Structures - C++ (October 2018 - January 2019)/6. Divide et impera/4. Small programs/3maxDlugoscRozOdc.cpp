#include <iostream>

double maxDlugosc(double sortedTab[], int n) {
     double with_tmp = 0, without_tmp = 0, with = 0, without = 0;

     for(int i = 1; i < n; i++) {
          without_tmp = std::max(with, without);
          with_tmp = without + sortedTab[i] - sortedTab[i-1];

          with = with_tmp;
          without = without_tmp;
     }

     return (with > without) ? with : without;
}

int main() {

     int n;

     std::cout << "Podaj rozmiar tablicy: " << std::flush;
     std::cin >> n;

     double tab[n];

     for(int i = 0; i < n; i++) {
          std::cin >> tab[i];
     }

     std::sort(tab, tab + n);

     for(int i = 0; i < n; i++) {
          std::cout << tab[i] << " " << std::flush;
     }

     double max = maxDlugosc(tab, n);

     std::cout << "Maksymalna dlugosc rozlacznych odcinkow wynosi: " << max << std::endl;



}