#ifndef QUEUE_HXX
#define QUEUE_HXX

using uint = unsigned int;

template <typename T>

class Queue {
private:
     uint head, tail, capacity;
     T *buf;
public:
     Queue (uint size): head(0), tail(0), capacity(size) { buf = new T[size]; };
     ~Queue() { delete[] buf; };
     void push(T x);     // Wstawia element x do kolejki (także enqueue)
     T pop();            // Usuwa element z kolejki (także dequeue) i zwraca jego wartość
     T& front();         // Zwraca referencję do najstarszego elementu (także peek)
     uint size();           // Zwraca liczbę elementów w kolejce
     bool empty();         // Sprawdza czy kolejka jest pusta
     bool full();          // Sprawdza czy kolejka jest pełna
     uint mask (uint);
};

template <typename T> 
uint Queue<T>::mask (uint value) {
     return value & (capacity - 1);
}

template <typename T>
void Queue<T>::push(T x) {
     buf[mask(tail++)] = x;
}

template <typename T>
T Queue<T>::pop() { 
     return buf[mask(head++)];
}

template <typename T>
T& Queue<T>::front() { 
     return buf[mask(head)];
}

template <typename T> 
uint Queue<T>::size() { 
     return tail-head;
}

template <typename T>
bool Queue<T>::empty() { 
     return size() == 0;
}

template <typename T>
bool Queue<T>::full() { 
     return size() == capacity;
}

#endif