#include <iostream>
#include <string>
#include "queue.hxx"

constexpr int n = 1024;

int main() {

     Queue<int> queue(n);
     std::string line;

     while(std::cin >> line) {
          switch(line.at(0)) {
               case 'A':
                    // Sprawdza czy kolejka jest pełna
                    if(!queue.full()) {
                         std::cin >> line;
                         int x = std::stoi(line);
                         std::cout << "Added " << x << " to the queue" << std::endl;
                         queue.push(x);
                    } else {
                         std::cout << "FULL" << std::endl;
                    }
                    break;
               case 'S':
                    std::cout << "There are " << queue.size() << " elements in queue" << std::endl;
                    break;
               case 'D':
                    // Sprawdza czy kolejka jest pusta
                    if(queue.empty()) {
                         std::cout << "EMPTY" << std::endl;
                    } else {
                         std::cout << "Removing " << queue.pop() << " from the queue" << std::endl;
                    }
                    break;
               case 'F':
                    std::cin >> line;
                    break;
               default:
                    break;
          }
     }

     return 0;
}
