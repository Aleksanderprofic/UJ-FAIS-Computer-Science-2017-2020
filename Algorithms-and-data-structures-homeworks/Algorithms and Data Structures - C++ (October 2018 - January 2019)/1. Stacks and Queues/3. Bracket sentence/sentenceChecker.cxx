#include <iostream>
#include <vector>
#include <ctime>

bool sentenceChecker(std::string sentence) {
     std::vector<char> openBrackets;
     int size = sentence.size();
     
     for(int i = 0; i < size; i++) {
          switch(sentence[i]) {
               case '(':
                    if(size-i > openBrackets.size()) {
                         openBrackets.push_back('(');
                    } else {
                         return false;
                    }
                    break;
               case ')':
                    if(!openBrackets.empty() && openBrackets.back() == '(') {
                         openBrackets.pop_back();
                    } else {
                         return false;
                    }
                    break;
               case '[':
                    if(size-i > openBrackets.size()) {
                         openBrackets.push_back('[');
                    } else {
                         return false;
                    }
                    break;
               case ']':
                    if(!openBrackets.empty() && openBrackets.back() == '[') {
                         openBrackets.pop_back();
                    } else {
                         return false;
                    }
                    break;
          }
     }

     return true;
}

int main() {

     std::string line;
     while(std::cin >> line) {
          std::cout << line << ": " << std::flush;

          if(sentenceChecker(line)) std::cout << "Correct" << std::endl;
          else std::cout << "Incorrect " << std::endl;

          
     }

}