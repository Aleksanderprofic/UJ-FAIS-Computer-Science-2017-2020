#include <iostream>
#include <ctime>
#include "sortedArrayList.hxx"

constexpr int n = 50000;

int main() {

     SortedArrayList sal(n);

     srand(time(NULL));

     for(int i = 0; i < n; i++) {
          sal.push(rand()%n);
     }

     for(int i = 0; i < n; i++) {
          sal.erase(rand()%sal.size());
     }

     return 0;
}