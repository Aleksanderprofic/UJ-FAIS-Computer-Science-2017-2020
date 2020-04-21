#include <iostream>
#include <vector>
#include <ctime>

char genRandomBracket() {

     switch(rand()%4) {
          case 0:
               return '(';
          case 1:
               return ')';
          case 2:
               return '[';
          case 3:
               return ']';
          default:
               return -1;
     }
}

std::vector<char> badSentenceGenerator(std::vector<char> sentence) {

     bool j = false, k = false;
     char c;

     for(int i = 0; i < sentence.size(); i++) {
          if(10%rand()%7+1 == 0) {
               k = false;
               while(!k) {
                   c = genRandomBracket();
                   if(c != sentence[i]) {
                       sentence[i] = c;
                       k = true;
                       j = true;
                   }
               }
          }
     }
     if(j == false) {
          while(!j) {
                   c = genRandomBracket();
                   int i = rand()%sentence.size();
                   if(c != sentence[i]) {
                       sentence[i] = genRandomBracket();
                       j = true;
                   }
               }
          
     }

     /*for(int i = 0; i < sentence.size(); i++) {
          std::cout << sentence[i] << std::flush;
     }

     std::cout << std::endl;
     */
    return sentence;
}

std::vector<char> badSentenceGenerator(int n) {

     std::vector<char> sentence;

     for(int i = 0; i < n; i++) {
          sentence.push_back(genRandomBracket());
     }

     /*for(int i = 0; i < n; i++) {
          std::cout << sentence[i] << std::flush;
     }

     std::cout << std::endl;*/
     return sentence;

}

std::vector<char> goodSentenceGenerator(int n) {

     if(n % 2 == 1) n++;

     std::vector<char> sentence, openBrackets;
     bool goodBracket = false;
     char c;

     for(int i = 0; i < n; i++) {
          while(!goodBracket) {
               switch(c = genRandomBracket()) {
                    case '(':
                         if(n-sentence.size() > openBrackets.size()) {
                              goodBracket = true;
                              openBrackets.push_back('(');
                         }
                         break;
                    case ')':
                         if(!openBrackets.empty() && openBrackets.back() == '(') {
                              goodBracket = true;
                              openBrackets.pop_back();
                         }
                         break;
                    case '[':
                         if(n-sentence.size() > openBrackets.size()) {
                              goodBracket = true;
                              openBrackets.push_back('[');
                         }
                         break;
                    case ']':
                         if(!openBrackets.empty() && openBrackets.back() == '[') {
                              goodBracket = true;
                              openBrackets.pop_back();
                         }
                         break;
               }
          }
          goodBracket = false;
          sentence.push_back(c);
     }

     /*for(int i = 0; i < n; i++) {
          std::cout << sentence[i] << std::flush;
     }*/
     
     return sentence;
}

std::vector<char> genSentence() {

     switch(rand()%4) {
          case 0: case 1:
               return goodSentenceGenerator((rand()%20)+10);
               break;
          case 2:
               return badSentenceGenerator(goodSentenceGenerator(rand()%20+10));
               break;
          case 3:
               return badSentenceGenerator(rand()%20+10);
               break;
     }
     return goodSentenceGenerator((rand()%20)+10);
}

int main() {

     srand(time(NULL));

     std::vector<char> sentence;
     int size;

     for(int i = 0; i < 10; i++) {
          sentence = genSentence();
          size = sentence.size();
          for(int j = 0; j < size; j++) {
               std::cout << sentence[j] << std::flush;
          }
          std::cout << std::endl;

          //std::cout << genSentence().data() << std::endl;
     }

     return 0;
}
