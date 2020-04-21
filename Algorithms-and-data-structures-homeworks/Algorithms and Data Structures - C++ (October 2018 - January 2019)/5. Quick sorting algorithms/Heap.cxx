#include "Heap.hxx"

// Wersja iteracyjna
void Heap::heapifyIter(int i) {

     int largest, c1, c2;
     while(i < max) {
          largest = i;
          c1 = 2*i;
          c2 = c1 + 1;

          if(c1 < max && heap[c1] > heap[largest]) largest = c1;
          if(c2 < max && heap[c2] > heap[largest]) largest = c2;

          if(largest == i) return;
          std::swap(heap[i], heap[largest]);
          i = largest;
     }
}
// Wersja rekurencyjna
void Heap::heapifyRec(int i) {
     int largest, c1, c2;
     while(i < max) {
          largest = i;
          c1 = 2*i;
          c2 = c1 + 1;

          if(c1 < max && heap[c1] > heap[largest]) largest = c1;
          if(c2 < max && heap[c2] > heap[largest]) largest = c2;

          if(largest == i) return;

          std::swap(heap[largest], heap[i]);
          heapifyRec(largest);
     }

     
}

void Heap::build(int *a, int s) {
     heap.clear();
     // Wrzucam cokolwiek na pozycje 0
     heap.push_back(s);
     for(int i = 0; i < s; i++) {
          heap.push_back(a[i]);
     }
     this->max = s+1;

     for(int i = s/2; i >= 1; i--) 
          heapifyIter(i);
}
// Wstawia element do kopca
void Heap::push(int x) {
     int i = heap[0]++;   // zwieksza ilość elementow w tablicy
     max = heap[0];
     heap[i] = x;

     int half = i/2;
     while(i > 1 && heap[i] > heap[half]) {
          std::swap(heap[i],heap[half]);
          i = half;
          half = i/2;
     }
}
// Usuwa element z kopca
int Heap::hop() {
     if(!empty()) {
          int ret = heap[1];
          heap.erase(++heap.begin());
          std::swap(heap[1], heap[heap.size()-1]);
          
          for(int i = size()/2; i >= 1; i--) 
               heapifyRec(i);
          
          max--;
          return ret;
     }
     return -1;
}  
// Zwraca referncję do ostatniego elementu
int& Heap::top() {
     return this->heap[size()-1];
}
// Zwraca liczbę elementów w kopcu      
int Heap::size() {
     return heap.size()-1;
}
// Sprawdza czy kopiec jest pusty
bool Heap::empty() {
     return heap.size()==1;
}

// Sprawdza czy właściwość kopca jest zachowana
bool Heap::check() { // jest zle
     int s = size();
     int half = s/2, ix2;
     for(int i = 1; i <= half; i = ix2) {
          ix2 = 2*i;
          if(ix2 <= s && (heap[i] < heap[ix2])) return false;
          if(ix2+1 <= s && (heap[i] < heap[ix2+1])) return false;
     }
     return true;
}

void Heap::sortRec(int * a, int s) {
     build(a, s);
     
     for(int i = size(); i > 1; i--) {
          std::swap(heap[1], heap[i]);
          max--;
          heapifyRec(1);
     }
}

void Heap::sortIter(int * a, int s) {
     build(a, s);

     for(int i = size(); i > 1; i--) {
          std::swap(heap[1], heap[i]);
          max--;
          heapifyIter(1);
     }
}

void Heap::printHeap() {
     int s = size();
     printf("| ");
     for(int i = 1; i <= s; i++) {
          printf("%d | ", heap[i]);
     }
     printf("\n");
}