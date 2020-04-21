#include <iostream>
#include <stack>
#include <string>

int main() {

     std::stack<int> stack;
     std::string line;

     while(std::cin >> line) {
          switch(line.at(0)) {
               case 'A':
                    if(stack.size() < 1000000) {
                         std::cin >> line;
                         int x = std::stoi(line);
                         std::cout << "Added " << x << " to the stack" << std::endl;
                         stack.push(x);
                    } else {
                         std::cout << "FULL" << std::endl;
                    }
                    break;
               case 'S':
                    std::cout << "There are " << stack.size() << " elements on the stack" << std::endl;
                    break;
               case 'D':
                    if(stack.empty()) {
                         std::cout << "EMPTY" << std::endl;
                    } else {
                         std::cout << "Removing " << stack.top() << " from the stack" << std::endl;
                         stack.pop();
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