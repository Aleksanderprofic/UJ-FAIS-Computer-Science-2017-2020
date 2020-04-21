#include <iostream>
#include <string>
#include "list"

int main() {

     std::list<int> list;
     /*
     list.pop_back();
     list.pop_front();
     list.pop_back();
     list.pop_front();
     list.pop_front();
     list.push_front(22);
     
     list.push_back(-12121);
     list.push_back(0);
     list.push_back(15);
     list.push_front(1234);
     
     list.insert(-222, 4);
     list.push_front(1202101221);
     list.push_front(-5);

     list.push_front(1111);
     
     list.erase(list.find(22));
     
     list.erase(list.find(1202101221));
     list.erase(list.find(0));
     list.pop_front();
     list.pop_back();
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
                         std::cout << "Pop front\t->>> Removing " << list.front() << " from the front of the list" << std::endl;
                         list.pop_front();
                    }
                    break;
               case 'b':
                    if(list.empty()) {
                         std::cout << "Pop back\t->>> EMPTY" << std::endl;
                    } else {
                         std::cout << "Pop back\t->>> Removing " << list.back() << " from the back of the list" << std::endl;
                         list.pop_back();
                    }
                    break;
               case 'C':
                    if(!list.empty()) {
                         std::cin >> line;
                         bool found = false;
                         x = stoi(line);

                         for(auto it=list.begin(); it != list.end(); it++) {
                              if(*it == x) {
                                   std::cout << "Find\t\t->>> TRUE" << x << std::endl;
                                   found = true;
                                   break;
                              }
                         }
                         if(!found) std::cout << "Find\t\t->>> FALSE" << std::endl;                
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
