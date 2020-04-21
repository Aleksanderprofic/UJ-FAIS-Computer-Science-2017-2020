#include <iostream>
#include <ctime>
#include "sortedLinkedList.hxx"

constexpr int n = 50000;

int main() {

     SortedLinkedList sll;

     srand(time(NULL));

     for(int i = 0; i < n; i++) {
          sll.push(rand()%n);
     }

     std::cout << "Sorted? " << sll.check() << std::endl;

     for(int i = 0; i < n; i++) {
          sll.erase(rand()%sll.size());
     }

     return 0;
}