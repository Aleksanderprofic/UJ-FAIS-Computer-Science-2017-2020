#include <iostream>
#include "sortedLinkedList.hxx"

int main() {
     
     int size;

     std::cin >> size;
     SortedLinkedList sll1;
     
     for(int i = 0, temp; i < size; i++) {
          std::cin >> temp;
          sll1.push(temp);
     }

     std::cout << "SortedLinkedList 1: " << std::endl;
     sll1.print();

     std::cin >> size;
     SortedLinkedList sll2;
     for(int i = 0, temp; i < size; i++) {
          std::cin >> temp;
          sll2.push(temp);
     }

     std::cout << "SortedLinkedList 2: " << std::endl;
     sll2.print();

     std::cout << "Merged: " << std::endl;
     SortedLinkedList sll = SortedLinkedList::merge(sll1, sll2);
     sll.print();

     std::cout << "Merged unique: " << std::endl;
     sll.unique();
     sll.print();

     return 0;
}