#include <iostream>
#include <string>
#include <cassert>
#include "stack.hxx"

constexpr int n = 10;

int main() {

     Stack<int> stack(n);
     std::string line;

     while(std::cin >> line) {
          switch(line.at(0)) {
               case 'A':
                    // sprawdza czy stos jest pełny
                    try {
                         std::cin >> line;
                         int x = std::stoi(line);
                         std::cout << "Added " << x << " to the stack" << std::endl;
                         stack.push(x);
                    } catch (std::out_of_range& e) {
                         std::cout << e.what() << std::endl;
                    }
                    break;
               case 'S':
                    std::cout << "There are " << stack.size() << " elements on the stack" << std::endl;
                    break;
               case 'D':
                    // sprawdza czy stos jest pusty
                    try {
                         auto temp = stack.pop();
                         std::cout << "Removing " << temp << " from the stack" << std::endl;
                    } catch (std::out_of_range& e) {
                         std::cout << e.what() << std::endl;
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