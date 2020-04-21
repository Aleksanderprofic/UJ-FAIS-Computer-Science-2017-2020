#include <iostream>
#include <ctime>
#include "sortedArrayList.hxx"

constexpr int n = 500;

int main(int argc, char* argv[]) {

     if(argc != 2) {
          perror("Not enough arguments.");
          exit(-1);
     }

     srand(time(NULL));

     int sizeOfTwoLists = atoi(argv[1]);

     int size1 = rand()%(sizeOfTwoLists-1)+1;
     SortedArrayList sal1(size1);
     int size2 = sizeOfTwoLists - size1;
     SortedArrayList sal2(size2);
     std::cout << size1 << std::endl;
     for(int i = 0; i < size1; i++) {
          sal1.push(rand()%(2*n)-n);
     }
     sal1.print();

     std::cout << size2 << std::endl;
     for(int i = 0; i < size2; i++) {
          sal2.push(rand()%(2*n)-n);
     }
     sal2.print();
}