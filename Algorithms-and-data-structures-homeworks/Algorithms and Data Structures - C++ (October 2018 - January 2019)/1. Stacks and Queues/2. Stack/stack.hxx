#ifndef STACK_HXX
#define STACK_HXX
#include <iostream>
#include <stdexcept>
#include <exception>


template<typename T>

class Stack {
private:
     int position, n;
     T *tab;
public:
     Stack(int size);
     ~Stack();

     void push(T x); // Wstawia element x na stos
     T pop();        // Usuwa element ze stosu i zwraca jego wartość
     T& top();       // Zwraca referencję do najmłodszego elementu
     int size();       // Zwraca liczbę elementów na stosie
     bool empty();     // Sprawdza czy stos jest pusty
     bool full();      // Sprawdza czy stos jest pełny
};

// konstruktor
template<typename T>
Stack<T>::Stack(int size): position(0), n(size) {
     tab = new T[size];
}

// destruktor dealokujacy pamiec przydzielona do tablicy
template<typename T>
Stack<T>::~Stack() {
     delete[] tab;
}

// dodawanie elementu do stosu
template<typename T>
void Stack<T>::push(T x) {
     if(full()) throw std::out_of_range("Exception: too much elements on the stack");
     tab[position] = x;
     position++;
}

// usuwanie elementu ze stosu
template<typename T>
T Stack<T>::pop() { 
     if(empty()) throw std::out_of_range("Exception: there are no elements to pop from the stack");
     position--;
     return tab[position];
}

// zwraca referencje do najmlodszego elementu
template<typename T>
T& Stack<T>::top() {
     return tab[position-1];
}

// zwraca liczbe elementow na stosie
template<typename T>
int Stack<T>::size() { 
     return position;
}

// sprawdza czy stos jest pusty
template<typename T>
bool Stack<T>::empty() {
     return (position == 0);
}

template<typename T>
bool Stack<T>::full() {
     return (position == n);
}

#endif