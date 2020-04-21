#include <iostream>
#include <cmath>
#include <vector>

constexpr double EPSILON = 10e-20;
constexpr double SECTION = 10e-5;

// Liczy wartość funkcji dla podanego x
double ourFunctionValue(double x);
// Liczy argument x3
double findx3(double x1, double x2);
// Wypisanie wszystkich miejsc zerowych
void printRoots(std::vector<double> roots);
// Funkcja implementująca regułę fałszywego połozenia
void regulaFalsi(double x1, double x2);

int main() { 
     double x1, x2, fx1, fx2;

     std::cout << "Obliczanie miejsc zerowych funkcji: (x^2-1)(sinhx)^3" << std::endl;
     do {
          std::cout << "Podaj krance przedziału: [x1, x2], w ktorych program ma szukać miejsc zerowych" << std::endl;
          std::cout << "x1 -> " << std::flush;
          std::cin >> x1;
          fx1 = ourFunctionValue(x1);
          std::cout << "x2 -> " << std::flush;
          std::cin >> x2;
          fx2 = ourFunctionValue(x2);
     } while((fx1*fx2) > 0);

     if(x1 > x2) std::swap(x1, x2);
     regulaFalsi(x1, x2);
}

double ourFunctionValue(double x) {
     return (x*x-1)*std::pow(sinh(x),3);
}

double findx3(double x1, double x2) {
     double fx1 = ourFunctionValue(x1);
     double fx2 = ourFunctionValue(x2);
     return (fx1*x2-fx2*x1)/(fx1-fx2);
}

void printRoots(std::vector<double> roots) {
     for(double x: roots)
          printf("%.5f\n", x);
}

void regulaFalsi(double x1, double x2) {
     // Lista miejsc zerowych funkcji
     std::vector<double> roots;
     double x3 = 0, fx1 = 0, fx2 = 0, fx3;
     double a, b;

     a = x1; b = x1 + SECTION;

     while(a < x2) {
          if(b > x2) b = x2;

          fx1 = ourFunctionValue(a);
          fx2 = ourFunctionValue(b);

          if(fx1*fx2 <= 0) {
               double tmpa = a, tmpb = b;
               // Szukanie miejsca zerowego
               x3 = findx3(a, b);
               fx3 = ourFunctionValue(x3);
               while(abs(fx3) > EPSILON) {
                    if(fx1*fx3 < 0) {
                         tmpa = a; 
                         tmpb = x3;
                    }
                    else if(fx3*fx2 < 0) {
                         tmpa = x3; 
                         tmpb = b;
                    }

                    x3 = findx3(tmpa, tmpb);
                    fx1 = ourFunctionValue(tmpa);
                    fx2 = ourFunctionValue(tmpb);
                    fx3 = ourFunctionValue(x3);
               }
               roots.push_back(x3);
          }
          a = b;
          b += SECTION;
     }     
     // wypisanie wszystkich miejsc zerowych
     printRoots(roots);
}