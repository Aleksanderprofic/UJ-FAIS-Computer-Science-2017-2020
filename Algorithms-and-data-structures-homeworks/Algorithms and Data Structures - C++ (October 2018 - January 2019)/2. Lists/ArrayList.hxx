#pragma once

#include <iostream>

using position_t = int;

template<typename T>

class ArrayList { 
private:
     int head, capacity;
     T* tab;

public:
     ArrayList(int);               // konstruktor
     ~ArrayList();                 // destruktor
     void push_front(T);           // Wstawia element na początek listy
     T pop_front();                // Usuwa element z początku listy i zwraca jego wartość
     void push_back(T);            // Wstawia element na koniec listy
     T pop_back();                 // Usuwa element z końca listy  i zwraca jego wartość
     position_t find(T);             // Wyszukuje element o wartości `x` i zwraca do niego wskaźnik lub `nullptr` gdy element nie istnieje
     position_t insert(position_t, T);     // Wstawia element na podanej pozycji
     position_t erase(position_t);            // Usuwa element z podanej pozycji
     bool full();
     bool empty();
     int size();                   // Zwraca liczbę elementów w liście

     void printList();
};

template<typename T>
ArrayList<T>::ArrayList(int size): head(0), capacity(size) {
     tab = new T[size];
}

template<typename T>
ArrayList<T>::~ArrayList() {
     delete[] tab;
}

template<typename T>
void ArrayList<T>::push_front(T x) {
     tab[head++] = x;
}

template<typename T>
T ArrayList<T>::pop_front() {
     if(!empty()) return tab[--head];
     return -1;
}

template<typename T>
void ArrayList<T>::push_back(T x) {
     int i;
     for(i = size(); i > 0; i--) {
          tab[i] = tab[i-1];
     }
     tab[0] = x;
     head++;
}

template<typename T>
T ArrayList<T>::pop_back() {
     if(!empty()) {
          int n = size();
          int temp = tab[0];
          for(int i = 1; i < n; i++) {
               tab[i-1] = tab[i];
          }
          head--;
          return temp;
     } else {
          return -1;
     }
}

template<typename T>
position_t ArrayList<T>::find(T x) {
     int n = size();
     for(int i = 0; i < n; i++) {
          if(tab[i] == x) return i;
     }
     return -1;
}

template<typename T>
position_t ArrayList<T>::insert(position_t pos, T x) {
     if(!(pos < 1 || pos > size()+1)) {
          int i = 0;
          for(i = size()+1; i >= pos; i--) {
               tab[i] = tab[i-1];
          }
          tab[pos-1] = x;
          head++;
          return pos-1;
     } else return -1;
}

template<typename T>
position_t ArrayList<T>::erase(position_t x) {
     int n = size();
     if(x < 0) return -1;
     else if(x >= n-1) {
          pop_front();
          return x+1;
     } else {
          for(int i = x; i < n; i++) {
               tab[i] = tab[i+1];
          }
          head--;
          return x+1;
     }
}

template<typename T>
bool ArrayList<T>::full() {
     return head == capacity;
}

template<typename T>
bool ArrayList<T>::empty() {
     return head == 0;
}

template<typename T>
int ArrayList<T>::size() {
     return head;
}

template<typename T>
void ArrayList<T>::printList() {
     for(int i = 0; i < size(); i++) {
          std::cout << tab[i] << " | " << std::flush;
     }

     std::cout << std::endl;
}