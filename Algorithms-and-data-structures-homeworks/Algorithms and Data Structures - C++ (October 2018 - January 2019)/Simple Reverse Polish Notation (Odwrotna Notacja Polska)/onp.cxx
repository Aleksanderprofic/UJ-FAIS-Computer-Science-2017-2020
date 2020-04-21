#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

double ONP() {
     std::vector<double> stack;
     std::stringstream ss;
     std::string temp;
     double result, loaded, loaded2;

     while(true) {
          std::cin >> temp;
          if(temp == "=") return stack.back();
          ss.clear();
          ss << temp;

          if(ss >> loaded) { 
               stack.push_back(loaded);
          } else {
               loaded = stack.back();
               stack.pop_back();

               loaded2 = stack.back();
               stack.pop_back();

               switch(temp[0]) {
                    case '+':
                         loaded += loaded2;
                         break;
                    case '-':
                         loaded -= loaded2;
                         break;
                    case '*':
                         loaded *= loaded2;
                         break;
                    case '/':
                         loaded /= loaded2;
                         break;
                    case '^':
                         loaded = pow(loaded2, loaded);
                         break;
                    default:
                         return -1;
               }
               
               stack.push_back(loaded);
          }
     }
}

int main() {

     double result = ONP();

     std::cout << "Twoj wynik: " << result << std::endl;
}