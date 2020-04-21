#pragma once

#include <iostream>

class SortedLinkedList {
     struct node {                 // Zagnieżdżona klasa węzła
          node() { this->x = 0; };
          node(int obj, node* prev, node* next) { this->x = obj; this->prev = prev; this->next = next; }
          int x;                   // Element przechowywany przez węzeł listy
          node* prev;              // Wskaźnik do poprzedniego węzła
          node* next;              // Wskaźnik do kolejnego węzła
     };
private:
     node main;                    // main.x - rozmiar listy
public:
     SortedLinkedList() { main.next = &main; main.prev = &main; main.x = 0; }
     void push(int x);   // Wstawia element 'x'
     int pop();          // Zwraca i usuwa pierwszy (najmniejszy) element
     int erase(int i);   // Usuwa element na pozycji 'i' i zwraca jego wartość
     int find(int x);    // Zwraca pozycję elementu o wartości 'x' lub -1 gdy nie znaleziono
     int size() const;         // Zwraca liczbę elementów w liście
     void remove(int x); // Usuwa wszystkie elementy równe 'x'
     static SortedLinkedList merge(const SortedLinkedList& a, const SortedLinkedList& b);
                         // Scala dwie posortowane listy i zwraca posortowaną listę
     void unique();      // Usuwa sąsiadujące duplikaty
     void print();       // Wypisuje elementy listy w porządku rosnącym
     bool check();
};

void SortedLinkedList::push(int x) {
     node* i;
     for(i = this->main.next; x > i->x && i != &this->main; i = i->next);

     node* p = new node(x, i->prev, i);
     i->prev->next = p;
     i->prev = p;

     // zwiększenie ilości elementow w liście
     main.x++;
}

int SortedLinkedList::pop() {
     if(size() > 0) {
          int popNumber = main.next->x;
          main.next = main.next->next;
          delete main.next->prev;
          // main.next->prev->prev = nullptr;
          // main.next->prev->x = 0;
          // main.next->prev->next = nullptr;
          main.next->prev = &main;
          main.x--;

          return popNumber;
     } return -1;
}

int SortedLinkedList::erase(int pos) {
     int n = size();
     if(pos < n && n > 0) {
          int j;
          node* i;
          
          for(j = 0, i = main.next; j != pos; i = i->next, j++);
          
          int popNumber = i->x;

          i->prev->next = i->next;
          i->next->prev = i->prev;


          /////////
          delete i;

          main.x--;
          return popNumber;
     } return -1;
}

int SortedLinkedList::find(int x) {
     int j = 0;
     for(node* i = main.next; i != &main; i = i->next, j++) {
          if(i->x == x) {
               return j;
          }
     }
     return -1;
}

int SortedLinkedList::size() const {
    return this->main.x;
}

void SortedLinkedList::remove(int x) {
     for(node* i = main.next; i != &main ; i = i->next) {
          if(i->x == x) {
               node *j = i->next, *temp = i;
               i = i->prev;
               for(; j->x == x; j = j->next, temp = j->prev) {
                    delete temp;
                    main.x--;
               }
               delete temp;
               main.x--;
               i->next = j;
               j->prev = i;
               return;
          }
     }
}

SortedLinkedList SortedLinkedList::merge(const SortedLinkedList& a, const SortedLinkedList& b) {
     SortedLinkedList other;

     for(node* i = a.main.next; i != &a.main ; i = i->next) {
          int temp = i->x;
          other.push(temp);
     }

     for(node* i = b.main.next; i != &b.main; i = i->next) {
          int temp = i->x;
          other.push(temp);
     }

     return other;
}

void SortedLinkedList::unique() {
     for(node* i = main.next; i != &main ; i = i->next) {
          if(i->x == i->next->x) {
               node *j = i->next->next;
               while(j->x == i->x && j != &main) {
                    delete j->prev;
                    main.x--;
                    j = j->next;
               }
               delete j->prev;
               main.x--;
               i->next = j;
               j->prev = i;
          }
     }
}

void SortedLinkedList::print() {
     if(size() > 0) {

          for(node* i = main.next; i != &main; i = i->next) {
               std::cout << i->x << " " << std::flush;
          }
          std::cout << std::endl;
     } else {
          std::cout << "Print\t->>>Empty list" << std::endl;
     }
}

bool SortedLinkedList::check() {
     
     for(node* i = main.next; i->next != &main; i = i->next) {
          if(i->x > i->next->x) return false;
     }
     return true;
}