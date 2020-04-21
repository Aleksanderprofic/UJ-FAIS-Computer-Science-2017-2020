#include <iostream>
#include "sortedArrayList.hxx"
#include "sortedLinkedList.hxx"
#include <list>



int main() { 

     int size1;

     std::cin >> size1;
     
     SortedArrayList sal1(size1);
     SortedLinkedList sll1;
     std::list<int> list1;

     
     for(int i = 0, temp; i < size1; i++) {
          std::cin >> temp;
          sal1.push(temp);
          sll1.push(temp);
          list1.push_front(temp);
     }
     list1.sort();


     int size2;

     std::cin >> size2;
     
     SortedArrayList sal2(size2);
     SortedLinkedList sll2;
     std::list<int> list2;
     
     for(int i = 0, temp; i < size2; i++) {
          std::cin >> temp;
          sal2.push(temp);
          sll2.push(temp);
          list2.push_front(temp);
     }
     list2.sort();
     



     SortedArrayList otherSal = SortedArrayList::merge(sal1, sal2);
     std::cout << "Merged ArrayList: " << std::endl;
     otherSal.print();



     SortedLinkedList otherSll = SortedLinkedList::merge(sll1, sll2);
     std::cout << "Merged LinkedList: " << std::endl;
     otherSll.print();



     list1.merge(list2);
     std::cout << "Merged std::list: " << std::endl;
     for(int i: list1) {
          std::cout << i << " " << std::flush;
     }
     std::cout << std::endl;






     std::cout << "Merged unique ArrayList: " << std::endl;
     otherSal.unique();
     otherSal.print();



     std::cout << "Merged unique LinkedList: " << std::endl;
     otherSll.unique();
     otherSll.print();



     list1.unique();
     std::cout << "Merged unique std::list: " << std::endl;
     for(int i: list1) {
          std::cout << i << " " << std::flush;
     }
     std::cout << std::endl;
     
     
     return 0;
}