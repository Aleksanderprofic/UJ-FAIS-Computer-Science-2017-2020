#ifndef LINKEDLIST_HXX
#define LINKEDLIST_HXX

#include <iostream>

class LinkedList { 
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
    using position_t = node*;
    LinkedList() {                  // konstruktor
        main.x = 0; main.next = &main; main.prev = &main; 
    }
    
    void push_front(int);           // Wstawia element na początek listy
    int pop_front();                // Usuwa element z początku listy i zwraca jego wartość
    void push_back(int);            // Wstawia element na koniec listy
    int pop_back();                 // Usuwa element z końca listy  i zwraca jego wartość
    position_t find(int);           // Wyszukuje element o wartości `x` i zwraca do niego wskaźnik lub `nullptr` gdy element nie istnieje
    position_t insert(position_t, int);          // Wstawia element na podanej pozycji
    position_t erase(position_t);          // Usuwa element z podanej pozycji
    void printList();
    bool empty();
    int size();                     // Zwraca liczbę elementów w liście
};

void LinkedList::push_front(int x) {
    node* newPointerNext = main.next;
    node* newObject = new node(x, &main, newPointerNext);
    
    main.next = newObject;
    newPointerNext->prev = newObject;
    // zwiększenie ilości elementow w liście
    main.x++;  
}

int LinkedList::pop_front() {
    if(!empty()) {
        
        main.next->prev = nullptr;
        main.next = main.next->next;
        main.next->prev->next = nullptr;

        int popValue = main.next->prev->x;

        main.next->prev = &main;

        // zmniejszenie ilości elementow w liście
        main.x--;  

        return popValue;
    }
    return -1;     
}

void LinkedList::push_back(int x) {
    node* newPointerPrev = main.prev;                     
    node* newObject = new node(x, newPointerPrev, &main);
    
    main.prev = newObject;
    newPointerPrev->next = newObject;
    // zwiększenie ilości elementow w liście
    main.x++;                 
}

int LinkedList::pop_back() {
    if(!empty()) {

        main.prev->next = nullptr;
        main.prev = main.prev->prev;
        main.prev->next->prev = nullptr;

        int popValue = main.prev->next->x;

        main.prev->next = &main;
        // zmniejszenie ilości elementow w liście
        main.x--;

        return popValue;
    }

    return -1;     
}

LinkedList::position_t LinkedList::find(int x) {
for(node* i = main.next; i!=&main; i=i->next) {
        if(i->x == x) return i;
}
return nullptr;
}

LinkedList::position_t LinkedList::insert(position_t pos, int x) {
    position_t i;
    for(i = main.next; i!=&main; i=i->next) {
        if(i==pos) {
            node* newPointer = new node(x, i->prev, i);

            i->prev = newPointer;
            newPointer->prev->next = newPointer;

            // zwiekszanie ilości elementow w liście
            main.x++;
            
            return newPointer;
        }
    }
    
    return nullptr;
}

LinkedList::position_t LinkedList::erase(position_t x) {
    if(!empty()) {
        for(node* i = main.next; i!=&main; i=i->next) {
            if(i == x) {
                node* temp = i->next;
                
                i->prev->next = i->next;
                i->next->prev = i->prev;
                
                delete i;

                // zmniejszenie ilości elementow w liście
                main.x--;
                
                return temp;
            }
        }
    }
    return nullptr;
}

void LinkedList::printList() {
    for(node* i = main.next; i!=&main; i=i->next) {
        std::cout << i->x << " " << std::flush;
    }
    std::cout << std::endl;
}

bool LinkedList::empty() {
    return main.x == 0;
}

int LinkedList::size() {
    return main.x;
}

#endif