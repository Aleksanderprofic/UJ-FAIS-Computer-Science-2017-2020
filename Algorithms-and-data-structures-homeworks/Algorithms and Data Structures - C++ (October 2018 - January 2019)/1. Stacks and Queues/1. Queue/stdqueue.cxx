#include <iostream>
#include <string>
#include <queue>

int main() {

     std::queue<int> queue;
     std::string line;
     
     while(std::cin >> line) {
          switch(line.at(0)) {
               case 'A':
                    if(queue.size() < 1000000) {
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
                    if(queue.empty()) {
                         std::cout << "EMPTY" << std::endl;
                    } else {
                         std::cout << "Removing " << queue.front() << " from the queue" << std::endl;
                         queue.pop();
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