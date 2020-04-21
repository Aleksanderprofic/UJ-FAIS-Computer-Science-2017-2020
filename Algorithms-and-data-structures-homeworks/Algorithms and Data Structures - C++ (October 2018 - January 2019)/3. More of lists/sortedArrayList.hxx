#pragma once

#include <iostream>

class SortedArrayList{
private:
    int capacity, lenght;
    int* tab;
public:
    SortedArrayList(int size): capacity(size), lenght(0) { tab = new int[size]; }
    void push(int x);   // Wstawia element 'x'
    int pop();          // Zwraca i usuwa pierwszy (najmniejszy) element
    int erase(int i);   // Usuwa element na pozycji 'i' i zwraca jego wartość
    int find(int x);    // Zwraca pozycję elementu o wartości 'x' lub -1 gdy nie znaleziono
    int size() const;   // Zwraca liczbę elementów w liście
    void remove(int x); // Usuwa wszystkie elementy równe 'x'
    static SortedArrayList merge(const SortedArrayList& a, const SortedArrayList& b);
                        // Scala dwie posortowane listy i zwraca posortowaną listę
    void unique();      // Usuwa sąsiadujące duplikaty
    void print() const;       // Wypisuje elementy listy w porządku rosnącym
};

void SortedArrayList::push(int x) {
    int n = this->lenght;
    
    if(n > 0) {
        if(n < this->capacity) {
            int* lower = std::lower_bound(&tab[0], &tab[n], x);
            
            for(int i = n; &tab[i] != lower; i--) {
                tab[i] = tab[i-1];
            }
            *lower = x;
            lenght++;
        } else {
            std::cout << "Push\t->>> List is full" << std::endl;
        }
    } else {
        tab[0] = x;
        lenght++;
    }
}

int SortedArrayList::pop() {
    int n = size();

    if(n > 0) {
        int temp = tab[0];
        for(int i = 0; i < n; i++) {
            tab[i] = tab[i+1];
        }
        tab[n-1] = 0;

        lenght--;
        return temp;
    } 
    std::cout << "Pop\t->>> List is empty. Returning -1" << std::endl;
    return -1;
}

int SortedArrayList::erase(int pos) {
    int n = size();

    if(pos < n && pos >= 0) {
        int temp = tab[pos];
        for(int i = pos; i < n-1; i++) {
            tab[i] = tab[i+1];
        }
        tab[n-1] = 0;

        lenght--;

        return temp;
    } else {
        std::cout << "Erase\t->>> Wrong position of the element.\nReturning -1" << std::endl;
        return -1;
    }
}

int SortedArrayList::find(int x) {
    int n = size();

    if(n > 0) {
        for(int i = 0; i < n; i++) {
            if(tab[i] == x) return i;
        }    
    }
    return -1;
}

int SortedArrayList::size() const {
    return this->lenght;
}

void SortedArrayList::remove(int x) {
    int n = size();
    int i = 0;
    if(n > 0) {
        while(i < lenght) {
            if(tab[i] == x) {
                for(int j = i; j < lenght-1; j++) {
                    tab[j] = tab[j+1];
                }
                tab[lenght-1] = 0;
                lenght--;
            } else i++;
        }
    } else {
        std::cout << "Remove\t->>> List is already empty" << std::endl;
    }
}

SortedArrayList SortedArrayList::merge(const SortedArrayList& a, const SortedArrayList& b) {
    SortedArrayList other(a.size()+b.size());

    for(int i = 0; i < a.size(); i++) {
        other.push(a.tab[i]);
    }

    for(int i = 0; i < b.size(); i++) {
        other.push(b.tab[i]);
    }

    return other;
}

void SortedArrayList::unique() {
    int n = size();
    if(n > 1) {
        int i = 0;
        int j = 0;
        while(i+1 < lenght) {
            int diff = 0;
            if(tab[i] == tab[i+1]) {
                diff++;
                for(j = i+2; j < lenght && tab[j] == tab[i]; j++) {
                    diff++;
                }

                for(; j < lenght; j++) {
                    tab[j-diff] = tab[j];
                }
                lenght -= diff;
            }
            i++;
        }
    } else {
        std::cout << "Remove\t->>> List is already empty" << std::endl;
    }
}

void SortedArrayList::print() const {
    int n = size();
    if(n > 0) {
        for(int i = 0; i < n; i++) {
            std::cout << tab[i] << " " << std::flush;
        }
        std::cout << std::endl;
    } else {
        std::cout << "Print\t->>>Empty list" << std::endl;
    }
}