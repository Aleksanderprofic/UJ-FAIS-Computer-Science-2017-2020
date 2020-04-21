#include <iostream>
#include "LinkedList.hxx"

int main() {

     LinkedList list;
     /*
     list.push_back(1);
     list.printList();
     list.push_back(3);
     list.printList();
     list.push_back(5);
     list.printList();
     list.pop_front();
     list.printList();
     
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
     list.insert(list.find(15), 4);
     list.printList();
     list.push_front(1202101221);
     list.push_front(-5);
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
     int x;

     while(std::cin >> line) {
          switch(line.at(0)) {
               case 'F':
                    std::cin >> line;
                    x = std::stoi(line);
                    std::cout << "Push front\t->>> Added " << x << " to the front" << std::endl;
                    list.push_front(x);
                    break;
               case 'B':
                    std::cin >> line;
                    x = std::stoi(line);
                    std::cout << "Push back\t->>> Added " << x << " to the back" << std::endl;
                    list.push_back(x);
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
                         x = stoi(line);
                         if((list.find(x)) != nullptr) {
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