#include <iostream>
#include "sortedArrayList.hxx"

int main() {

     int size;

     std::cin >> size;
     SortedArrayList sal1(size);
     
     for(int i = 0, temp; i < size; i++) {
          std::cin >> temp;
          sal1.push(temp);
     }

     std::cout << "SortedArrayList 1: " << std::endl;
     sal1.print();

     std::cin >> size;
     SortedArrayList sal2(size);
     for(int i = 0, temp; i < size; i++) {
          std::cin >> temp;
          sal2.push(temp);
     }

     std::cout << "SortedArrayList 2: " << std::endl;
     sal2.print();

     std::cout << "Merged: " << std::endl;
     sal1 = SortedArrayList::merge(sal1, sal2);
     sal1.print();

     std::cout << "Merged unique: " << std::endl;
     sal1.unique();
     sal1.print();
     
     return 0;
}