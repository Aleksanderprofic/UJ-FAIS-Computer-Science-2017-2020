#pragma once

#include <iostream>
#include <vector>

class Heap {
private:
     std::vector<int> heap;
     int max;
     void heapifyIter(int);    // Wersja iteracyjna
     void heapifyRec(int);     // Wersja rekurencyjna
public:
     Heap(): max(-1) {
          heap.push_back(0);
     };

     Heap(int *tab, int size) {
          build(tab, size);
     };
     
     void build(int*, int);
     void push(int x);         // Wstawia element do kopca
     int hop();                // Usuwa element z kopca
     int& top();               // Zwraca referncję do ostatniego elementu
     int size();               // Zwraca liczbę elementów w kopcu
     bool full();              // Sprawdza czy kopiec jest pełny
     bool empty();             // Sprawdza czy kopiec jest pusty
     bool check();             // Sprawdza czy właściwość kopca jest zachowana
     void sortRec(int*, int);
     void sortIter(int*, int);
     void printHeap();
};

