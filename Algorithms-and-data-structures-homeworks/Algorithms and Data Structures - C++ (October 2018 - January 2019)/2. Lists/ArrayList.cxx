#include <iostream>
#include <string>
#include "ArrayList.hxx"

constexpr int n = 512;

int main() {

     ArrayList list(n);
     /*
     list.pop_back();
     list.pop_front();
     list.pop_back();
     list.pop_front();
     list.pop_front();
     list.push_front(22);
     list.printList();
     list.push_back(-12121);
     list.push_back(0);
     list.push_back(15);
     list.push_front(1234);
     list.printList();
     list.insert(1, -222);
     list.printList();
     list.push_front(1202101221);
     list.push_front(-5);
     list.printList();
     list.insert(0, 65);
     list.printList();
     list.push_front(1111);
     list.printList();
     list.erase(list.find(22));
     list.printList();
     list.erase(list.find(1202101221));
     list.erase(list.find(0));
     list.printList();
     list.pop_front();
     list.pop_back();
     list.printList();
     */
     
     std::string line;

     while(std::cin >> line) {
          switch(line.at(0)) {
               case 'F':
                    if(!list.full()) {
                         std::cin >> line;
                         int x = std::stoi(line);
                         std::cout << "Push front\t->>> Added " << x << " to the front" << std::endl;
                         list.push_front(x);
                    } else {
                         std::cout << "Push front\t->>> FULL" << std::endl;
                    }
                    break;
               case 'B':
                    if(!list.full()) {
                         std::cin >> line;
                         int x = std::stoi(line);
                         std::cout << "Push back\t->>> Added " << x << " to the back" << std::endl;
                         list.push_back(x);
                    } else {
                         std::cout << "Push back\t->>> FULL" << std::endl;
                    }
                    break;
               case 'S':
                    std::cout << "Size\t\t->>> There are " << list.size() << " elements in the list" << std::endl;
                    break;
               case 'f':
                    if(list.empty()) {
                         std::cout << "Pop front\t->>> EMPTY" << std::endl;
                    } else {
                         std::cout << "Pop front\t->>> Removing " << list.pop_front() << " from the front of the list" << std::endl;
                    }
                    break;
               case 'b':
                    if(list.empty()) {
                         std::cout << "Pop back\t->>> EMPTY" << std::endl;
                    } else {
                         std::cout << "Pop back\t->>> Removing " << list.pop_back() << " from the back of the list" << std::endl;
                    }
                    break;
               case 'C':
                    if(!list.empty()) {
                         std::cin >> line;
                         int position;
                         int x = stoi(line);
                         if((position = list.find(x)) != -1) {
                              std::cout << "Find\t\t->>> TRUE" << x << std::endl;
                         } else {
                              std::cout << "Find\t\t->>> FALSE" << std::endl;
                         }                         
                    } else {
                         std::cout << "Find\t\t->>> EMPTY" << std::endl;
                    }
                    break;
               default:
                    break;
          }
     }

     return 0;
}
