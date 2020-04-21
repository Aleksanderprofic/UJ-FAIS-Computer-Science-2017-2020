#ifndef CURSORLIST_HXX
#define CURSORLIST_HXX

#include <iostream>

using position_t = int;

class CursorList { 
     struct node {                 // Zagnieżdżona klasa węzła
          node() { this->x = 0; };
          int x;                     // Element przechowywany przez węzeł listy
          int next;                  // Indeks kolejnego węzła
     };

private:
     node* arr;
     int head;         // Indeks pierwszego węzła
     int size_;         // Ew. rozmiar listy
     int free;         // Ew. indeks pierwszego nieużytego elementu tablicy
     int n;            // Aktualna liczba elementow w tablicy

public: 
     CursorList(int);
     ~CursorList();
     void push_front(int);           // Wstawia element na początek listy
     int pop_front();                // Usuwa element z początku listy i zwraca jego wartość
     void push_back(int);            // Wstawia element na koniec listy
     int pop_back();                 // Usuwa element z końca listy  i zwraca jego wartość
     position_t find(int);           // Wyszukuje element o wartości `x` i zwraca do niego wskaźnik lub `nullptr` gdy element nie istnieje
     position_t insert(position_t, int);   // Wstawia element na podanej pozycji
     position_t erase(position_t);          // Usuwa element z podanej pozycji
     bool full();
     bool empty();
     int size();
     int getSize();
     void printList();
     void printWholeArray();
};

CursorList::CursorList(int size): head(-1), size_(size), free(0), n(0) {
     arr = new node[size];
     int i;
     for(i = 0; i < size-1; i++) {
          arr[i].x = 0;
          arr[i].next = i+1;
     }
     arr[i].x = 0;
     arr[i].next = -1;
}

CursorList::~CursorList() {
     delete arr;
}

void CursorList::push_front(int x) { //
     if(!full()) {
          int nextFree = arr[free].next;

          arr[free].x = x;
          arr[free].next = head;
          head = free;
          free = nextFree;
          n++;
     }
}

int CursorList::pop_front() {
     if(!empty()) {
          int popNumber = arr[head].x;
          arr[head].x = 0;
          int nextIndex = arr[head].next;
          int firstFree = free;

          free = head;
          arr[free].next = firstFree;
          head = nextIndex;
          n--;

          return popNumber;
     }
     return -1;
}

void CursorList::push_back(int x) {
     if(!full()) {
          if(!empty()) {
               int nextFree = arr[free].next;
               arr[free].x = x;
               arr[free].next = -1;

               int i = head;
               while(arr[i].next != -1) {
                    i = arr[i].next;
               }

               arr[i].next = free;
               
               free = nextFree;
          } else {
               head = free;
               int nextFree = arr[free].next;
               arr[free].x = x;
               arr[free].next = -1;

               free = nextFree;
          }
          n++;
     }
}

int CursorList::pop_back() {
     if(!empty()) {
          if(arr[head].next == -1) {
               int popNumber = arr[head].x;
               arr[head].x = 0;
               arr[head].next = free;
               free = head;
               head = -1;
               n = 0;
               return popNumber;
          } else {
               int firstFree = free;
               int i = arr[head].next, j = head;

               while(arr[i].next != -1) {
                    j = i;
                    i = arr[i].next;
               }
               arr[j].next = -1;

               free = i;
               arr[free].next = firstFree;
               int popNumber = arr[free].x;
               arr[free].x = 0;
               n--;
               return popNumber;
          }
     }
     return -1;
}

position_t CursorList::find(int x) {
     if(!empty()) {
          for(int i = head; i != -1; i=arr[i].next) {
               if(arr[i].x == x) return i;
          }
     }
     return -1;
}

position_t CursorList::insert(position_t pos, int x) {
     if(!full() && (pos < getSize() && pos >= 0)) {          
          if(head == pos) {
               int nextFree = arr[free].next;

               arr[free].x = x;
               arr[free].next = head;
               head = free;
               free = nextFree;
               n++;
               return head;
          } else {
               for(int i = head; i != -1; i = arr[i].next) {
                    if(arr[i].next == pos) {
                         int posOfNewElement = free;

                         int nextFree = arr[free].next;
                         arr[free].x = x;
                         arr[i].next = free;
                         arr[free].next = pos;



                         free = nextFree;
                         n++;
                         return posOfNewElement;
                    }
               }
          }
     }
     return -1;
}

position_t CursorList::erase(position_t pos) {
     if(!empty() && (pos < getSize() && pos >= 0)) {
          if(head == pos) {
               int nextIndex = arr[head].next;

               arr[head].x = 0;
               arr[head].next = free;
               free = head;
               head = nextIndex;
               n--;
               return nextIndex;
          } else {
               for(int i = head; i != -1; i = arr[i].next) {
                    if(arr[i].next == pos) {
                         int nextIndex = arr[pos].next;
                         arr[i].next = nextIndex;

                         // zerowanie i przepinanie usuwanej komorki
                         arr[pos].x = 0;
                         arr[pos].next = free;

                         free = pos;
                         n--;
                         return nextIndex;
                    }
               }
          }
     }
     return -1;
}

bool CursorList::full() {
     return (free == -1);
}

bool CursorList::empty() {
     return (head == -1);
}

int CursorList::getSize() {
     return size_;
}

int CursorList::size() {
     return n;
}

void CursorList::printList() {
     int i;

     for(i = head; i != -1; i = arr[i].next) {
          std::cout << "[" << arr[i].x << "|" << arr[i].next << "]" << std::flush;
     }
     std::cout << std::endl;
}

void CursorList::printWholeArray() {

     std::cout << "\nHead: " << head << "\nFree: " << free << std::endl;
     for(int i = 0; i < getSize(); i++) {
          std::cout << "[" << arr[i].x << "|" << arr[i].next << "] " << std::flush;
     }
     std::cout << std::endl;
}

#endif