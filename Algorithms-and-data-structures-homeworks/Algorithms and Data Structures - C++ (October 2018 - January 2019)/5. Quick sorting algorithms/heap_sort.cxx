#include <iostream>
#include "Heap.cxx"
#include <chrono>

int main(int argc, char * argv[]) {
     if(argc < 2) {
          std::cerr << "Usage :: ./heap_sort.x number_of_elements" << std::endl; 
          exit(-1);
     }

     const int N = atoi(argv[1]);

     int i;
     int tab[N];

     for(i = 0; i < N; i++) {
          std::cin >> tab[i];
     }

     Heap heap;

     heap.sortIter(tab, N);

     heap.printHeap();

     return 0;
}