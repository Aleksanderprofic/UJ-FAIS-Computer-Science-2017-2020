#include "AVL.hpp"
#include <fstream>

int main() {

     std::ios_base::sync_with_stdio(false);
     std::ifstream file("words.txt");
     AVL dict;
     std::string word;

     while(file >> word) 
          dict.insert(word);

     do {
          std::cout << "Find word: " << std::flush;
          std::cin >> word;

          if(word.compare("'end'") == 0) break;

          if(dict.search(word) == nullptr) 
               std::cout << "No" << std::endl;
          else std::cout << "Yes" << std::endl;
     } while(true);

     file.close();
}