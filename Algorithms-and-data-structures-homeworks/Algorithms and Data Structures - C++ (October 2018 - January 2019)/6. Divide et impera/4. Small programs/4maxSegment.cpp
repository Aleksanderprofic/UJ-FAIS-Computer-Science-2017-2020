#include <iostream>

int maxSegment(int tab[], int n) {
     int min_sum = 0, act_sum = 0, max = 0;

     for(int i = 0; i < n; i++) {
          act_sum += tab[i];
          min_sum = std::min(min_sum, act_sum);
          max = std::max(max, act_sum - min_sum);
     }
     return max;
}

int main() {
     int n;

     std::cout << "Podaj rozmiar tablicy: " << std::flush;
     std::cin >> n;

     int tab[n];

     for(int i = 0; i < n; i++) {
          std::cin >> tab[i];
     }

     int max = maxSegment(tab, n);
     std::cout << "Maksymalna suma segmentu to: " << max << std::endl;
}