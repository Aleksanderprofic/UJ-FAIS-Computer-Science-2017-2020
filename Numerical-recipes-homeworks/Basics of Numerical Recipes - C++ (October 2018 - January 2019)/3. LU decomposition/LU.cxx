#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

/* kolory w terminalu */
#define KG "\x1B[32m"   /* zielony */
#define KY "\x1B[33m"   /* zolty */
#define KR "\x1B[31m"   /* czerwony */
#define CY "\x1B[36m"   /* jasny niebieski */
#define LP "\x1B[35m"   /* fioletowy */
#define RESET "\x1B[0m" /* powrot do normalnego koloru */

using namespace std;

// Przeprowadza eliminacje Gaussa na macierzy tab wraz z wyborem elementu podstawowego oraz zwraca wektor permutacji
// Wartości macierzy L i U przechowuje w tej samej macierzy w celu oszczędzania pamięci
vector<double> gaussElimination(vector<vector<double> >& tab);
// Oblicza iloczyn skalarny dwoch wektorow
double scalarProduct(const vector<double>& a, vector<double>& b);
// Mnozenie dwoch macierzy
vector<vector<double> > multiply(const vector<vector<double> >& A, const vector<vector<double> >& B);
// Tworzy macierz permutacji P
vector<vector<double> > makePermutationMatrix(vector<double>& p);
// Rysuje w terminalu w odpowiednich miejscach literki P, A, L i U
void drawUpperPALU(int n);
// Rysuje w terminalu zawartość macierzy P, A, L i U
void drawPALU(const vector<vector<double> >& P, 
                 const vector<vector<double> >& A, 
                 const vector<vector<double> >& L, 
                 const vector<vector<double> >& U);
// Rysuje w terminalu w odpowiednich miejscach literki P, A i LU
void drawUpper(int n);
// Rysuje w terminalu zawartość macierzy P, A i LU
void drawResults(const vector<vector<double> >& P, const vector<vector<double> >& A, const vector<vector<double> >& LU);
// Wywołuje wszystkie funkcje draw -> wypisuje wyniki w terminalu
void printResults(const vector<vector<double> >& A, vector<vector<double> >& LU, vector<double>& p);
// Wypisuje mozliwosci uzytkownika na starcie programu
void printMenu();
// Wypisuje elementy związane z wyborem wymiaru macierzy oraz zwraca wymiar
int printAndReturnDimensions();
// Wypisuje elementy związane z wpisywaniem liczb do macierzy oraz zwraca utworzoną macierz
vector<vector<double> > printAndReturnMatrix(int size);


int main(int argc, char *argv[]) {
     system("clear");
     if(argc != 1) {
          printf(KR "Program arguments ignored.\n" RESET);
     }
     bool quit = false;
     

     string line;

     while(!quit) {
          printMenu();
          cin >> line;

          if(line.size() == 1 && isdigit(line[0])) {
               switch(line[0]) {
                    case '1': {
                         bool cont = false;
                         int size ;
                         if((size = printAndReturnDimensions()) == -1) {
                              printf(KR "\tYou can't make matrix with 0 dimensions. Try again :)\n" RESET);
                         } else {
                              vector<vector<double> > matrixA = printAndReturnMatrix(size);

                              vector<vector<double> > A(matrixA);

                              vector<double> p = gaussElimination(matrixA);

                              printResults(A, matrixA, p);

                              printf(KR "\n\n\n\tWould you like to continue to the menu?\n" RESET);
                              printf("\t\t1 -> yes\n");
                              printf("\t\tOther character will close application.\n");

                              while(!cont) {
                                   std::cin >> line;

                                   if(line.size() == 1 && isdigit(line[0])) {
                                        switch(line[0]) {
                                             case '1':
                                                  system("clear");
                                                  cont = true;
                                                  break;
                                             default:
                                                  cont = true;
                                                  quit = true;
                                                  break;
                                        }
                                   } else printf(KR "\tWrong number. Try again :)\n" RESET);
                              }
                         }
                    }
                         break;
                    default:
                         quit = true;
                         break;
               }
          } else {
               system("clear");
               printf(KR "\tWrong choice. Try again :)\n" RESET);
          }
     }
     return 0;
}

// Eliminacja Gaussa -> zwraca wektor permutacji p
vector<double> gaussElimination(vector<vector<double> >& tab) {
     int n = tab[0].size();
     // tablica permutacji
     vector<double> p(n);

     for(int i = 0; i < n; i++) { 
          p[i] = i;
     }

     for(int i = 0; i < n-1; i++) {
          int j, max = i;

          for(j = i+1; j < n; j++) {
               if(abs(tab[p[j]][i]) > abs(tab[p[max]][i])) max = j;
          }
          swap(p[i],p[max]);

          for(j = i+1; j < n; j++) {
               // Wyznaczenie jednego elementu macierzy L
               tab[p[j]][i] /= tab[p[i]][i];

               // Odejmowanie reszty elementow w wierszu
               for(int k = i+1; k < n; k++) {
                    tab[p[j]][k] -= tab[p[j]][i]*tab[p[i]][k];
               }
          }
     }
     return p;
}

// Oblicza iloczyn skalarny wektorow a i b
double scalarProduct(const vector<double>& a, vector<double>& b) {
     int size;
     if((size = a.size()) != b.size()) {
          std::cout << KR "\tUnable to compute scalarProduct. Sizes are not equal." RESET << std::endl;
          exit(-1);
     } else {
          double product = 0;
          for(int i = 0; i < size; i++) {
               product += a[i]*b[i];
          }
          return product;
     }
}

// Mnozenie macierzy A i B
vector<vector<double> > multiply(const vector<vector<double> >& A, const vector<vector<double> >& B) {
     int n;
     if((n = A.size()) != B.size()) {
          std::cout << KR "\tUnable to multiply. Sizes are not equal." RESET << std::endl;
          exit(-1);
     } else {
          vector<vector<double> > temp(A);
          for(int i = 0; i < n; i++) {
               for(int j = 0; j < n; j++) {
                    temp[i][j] = 0;
                    for(int k = 0; k < n; k++) {
                         temp[i][j] += A[i][k]*B[k][j];
                    }
               }
          }
          
          return temp;
     }
}

vector<vector<double> > makePermutationMatrix(vector<double>& p) {
     int n = p.size();

     vector<vector<double> > P(n);

     for(int i = 0; i < n; i++) {
          P[i].resize(n);
     }

     for(int i = 0; i < n; i++) {
          P[i][p[i]] = 1;
     }

     return P;
}

void drawUpperPALU(int n) {
     int size = n + n - 1;
     int i;
     printf("\n\n");

     for(int i = 0; i < size; i++) {
          if(i == size/2) printf(CY "P" RESET);
          else printf(" ");
     }
     printf("   \t");

     size = n*5+(n-1)*3;
     for(i = 0; i < size; i++) {
          if(i == size/2) printf("X");
          else printf(" ");
     }
     printf("   \t");
     for(i = 0; i < size; i++) {
          if(i == size/2) printf(KY "L" RESET);
          else printf(" ");
     }
     printf("   \t");
     for(i = 0; i < size; i++) {
          if(i == size/2) printf(KG "U" RESET);
          else printf(" ");
     }
     printf("\n");
}

void drawPALU(const vector<vector<double> >& P, 
                 const vector<vector<double> >& A, 
                 const vector<vector<double> >& L, 
                 const vector<vector<double> >& U) {

     int n = A[0].size();
     int half = n/2;

     for(int i = 0; i < n; i++) {  // Wiersze

          // Macierz permutacji P 
          for(int j = 0; j < n; j++) {
               if(P[i][j] == 1) printf(CY "%.0f " RESET, P[i][j]);
               else printf("%.0f " , P[i][j]);
          }
          
          if(i != half) printf("   \t");
          else printf("  *\t");


          // Macierz A
          for(int j = 0; j < n; j++) {
               double temp = A[i][j];
               if((temp > -1000000 && temp <= -10000) || (temp >= 100000 && temp < 10000000)) printf("%.0f\t", temp);
               else if((temp > -10000 && temp <= -1000) || (temp >= 10000 && temp < 100000)) printf("%.1f\t", temp);
               else if((temp > -1000 && temp <= -100) || (temp >= 1000 && temp < 10000)) printf("%.2f\t", temp);
               else if((temp > -100 && temp <= -10) || (temp >= 100 && temp < 1000)) printf("%.3f\t", temp);
               else if((temp > -10 && temp < 0) || (temp >= 10 && temp < 100)) printf("%.4f\t", temp);
               else if(temp >= 0 && temp < 10) printf("%.5f\t", temp);

          }
          if(i != half) printf("   \t");
          else printf("  =\t");

          // Macierz L
          for(int j = 0; j < n; j++) {
               double temp = L[i][j];
               if(i >= j) {
                    printf(KY);
               }

               // Wszystkie te warunki po to, aby ładnie wypisywało w terminalu maksymalnie 7 znakow łącznie ze znakami '.' i '-'
               if((temp > -1000000 && temp <= -10000) || (temp >= 100000 && temp < 10000000)) printf("%.0f\t", temp);
               else if((temp > -10000 && temp <= -1000) || (temp >= 10000 && temp < 100000)) printf("%.1f\t", temp);
               else if((temp > -1000 && temp <= -100) || (temp >= 1000 && temp < 10000)) printf("%.2f\t", temp);
               else if((temp > -100 && temp <= -10) || (temp >= 100 && temp < 1000)) printf("%.3f\t", temp);
               else if((temp > -10 && temp < 0) || (temp >= 10 && temp < 100)) printf("%.4f\t", temp);
               else if(temp >= 0 && temp < 10) printf("%.5f\t", temp);
               else printf("UPS\t");

               printf(RESET);
          }
          if(i != half) printf("   \t");
          else printf("  *\t");

          // Macierz U
          for(int j = 0; j < n; j++) {
               double temp = U[i][j];
               
               if(i <= j) {
                    printf(KG);
               }
               if((temp > -1000000 && temp <= -10000) || (temp >= 100000 && temp < 10000000)) printf("%.0f\t", temp);
               else if((temp > -10000 && temp <= -1000) || (temp >= 10000 && temp < 100000)) printf("%.1f\t", temp);
               else if((temp > -1000 && temp <= -100) || (temp >= 1000 && temp < 10000)) printf("%.2f\t", temp);
               else if((temp > -100 && temp <= -10) || (temp >= 100 && temp < 1000)) printf("%.3f\t", temp);
               else if((temp > -10 && temp < 0) || (temp >= 10 && temp < 100)) printf("%.4f\t", temp);
               else if(temp >= 0 && temp < 10) printf("%.5f\t", temp);
               else printf("UPS\t");

               printf(RESET);
          }

          printf("\n");
     }
}

void drawUpper(int n) {
     int size = n + n - 1;
     int i;

     for(int i = 0; i < size; i++) {
          if(i == size/2) printf(CY "P" RESET);
          else printf(" ");
     }
     printf("   \t");

     size = n*5+(n-1)*3;
     for(i = 0; i < size; i++) {
          if(i == size/2) printf("X");
          else printf(" ");
     }
     printf("   \t");
     for(i = 0; i < size; i++) {
          if(i == size/2) printf(KY "L" KG "U" RESET);
          else printf(" ");
     }
     printf("\n");
}

void drawResults(const vector<vector<double> >& P, const vector<vector<double> >& A, const vector<vector<double> >& LU) {
     int n = P[0].size();
     int half = n/2;
     
     for(int i = 0; i < n; i++) {
          // Macierz permutacji P 
          for(int j = 0; j < n; j++) {
               if(P[i][j] == 1) printf(CY "%.0f " RESET, P[i][j]);
               else printf("%.0f " , P[i][j]);
          }
          if(i != half) printf("   \t");
          else printf("  *\t");

          // Macierz A
          for(int j = 0; j < n; j++) {
               double temp = A[i][j];
               if((temp > -1000000 && temp <= -10000) || (temp >= 100000 && temp < 10000000)) printf("%.0f\t", temp);
               else if((temp > -10000 && temp <= -1000) || (temp >= 10000 && temp < 100000)) printf("%.1f\t", temp);
               else if((temp > -1000 && temp <= -100) || (temp >= 1000 && temp < 10000)) printf("%.2f\t", temp);
               else if((temp > -100 && temp <= -10) || (temp >= 100 && temp < 1000)) printf("%.3f\t", temp);
               else if((temp > -10 && temp < 0) || (temp >= 10 && temp < 100)) printf("%.4f\t", temp);
               else if(temp >= 0 && temp < 10) printf("%.5f\t", temp);
               else printf("UPS\t");
          }
          if(i != half) printf("   \t");
          else printf("  =\t");

          // Macierz LU
          for(int j = 0; j < n; j++) {
               double temp = LU[i][j];
               if((temp > -1000000 && temp <= -10000) || (temp >= 100000 && temp < 10000000)) printf("%.0f\t", temp);
               else if((temp > -10000 && temp <= -1000) || (temp >= 10000 && temp < 100000)) printf("%.1f\t", temp);
               else if((temp > -1000 && temp <= -100) || (temp >= 1000 && temp < 10000)) printf("%.2f\t", temp);
               else if((temp > -100 && temp <= -10) || (temp >= 100 && temp < 1000)) printf("%.3f\t", temp);
               else if((temp > -10 && temp < 0) || (temp >= 10 && temp < 100)) printf("%.4f\t", temp);
               else if(temp >= 0 && temp < 10) printf("%.5f\t", temp);
               else printf("UPS\t");

          }
          printf("\n");
     }     
}

void printResults(const vector<vector<double> >& A, vector<vector<double> >& LU, vector<double>& p) {
     vector<vector<double> > P = makePermutationMatrix(p);

     int n = A[0].size();

     LU = multiply(P, LU);
     
     vector<vector<double> > L(LU), U(LU);

     // Wyzerowanie elementow ponizej diagonali
     for(int i = 0; i < n; i++) {
          for(int j = i+1; j < n; j++) {
               U[j][i] = 0;
          }
     }

     // Wyzerowanie elementow nad diagonalą i ustawienie diagonali na 1
     for(int i = 0; i < n; i++) {
          for(int j = i; j < n; j++) {
               if(i < j) L[i][j] = 0;
               else L[i][j] = 1;
          }
     }

     std::cout << KR "\n\tThat's your decomposition!" RESET << std::endl;

     drawUpperPALU(n);
     drawPALU(P, A, L, U);

     std::cout << KR "\n\tLet's multiply " KY "L" KR " by " KG "U" KR ". See what I got?" RESET << std::endl;
     LU = multiply(L, U);

     printf("\n\n");
     drawUpper(n);
     drawResults(P, A, LU);

     std::cout << KR "\n\tNow " CY "P " RESET "* X " KR "should be equal to " KY "L" KG "U" KR " :)\n\tIf it's not then blame Aleksander :(" RESET << std::endl;
}

void printMenu() {
     std::cout << LP "\x1b[4m\n\tLU MAKER v1.0 by ALEKSANDER PROFIC\n" RESET << std::endl;
     std::cout << "\t1 -> Compute LU decomposition " << std::endl;
     std::cout << "\tOther character will close application.\n" << std::endl;
}

int printAndReturnDimensions() {
     std::string line;
     std::cout << "\tHow many dimensions has your matrix? \n" << std::flush;
     std::cin >> line;
     int dim;

     while(line.size() != 1 || !isdigit(line[0]) || (dim = stoi(line)) > 8) { 
          std::cout << KR "\tError. Too many characters or number is greater than " CY "8" KR ". \n\tMaximum " CY "8" KR " dimensions because only 8 fits nice in my terminal when it's set to maximum size :)\n" RESET << std::endl;
          std::cin >> line;
     }

     if(dim == 0) return -1;

     return dim;
}

vector<vector<double> > printAndReturnMatrix(int size) {
     std::string line;

     vector<vector<double> > A(size);
     for(int i = 0; i < size; i++) {
          A[i].resize(size);
     }

     for(int i = 0; i < size; i++) {
          std::cout << "\n\tEnter the " KR << i+1 << RESET " row: (seperate by a space or enter) " << std::endl;
               
          for(int j = 0; j < size; j++) {
               bool isnumber = false;

               while(!isnumber) {
                    bool isdot = false;
                    cin >> line;
                    int k;
                    if(line.size() <= 7) {
                         if(isdigit(line[0]) || line[0] == '-' || line[0] == '+' || line[0] == '.') {
                              if(line[0] == '.') isdot = true;
                              for(k = 1; k < line.size(); k++) {
                                   if(!isdigit(line[k])) {
                                        if(line[k] == '.' && !isdot) {
                                             isdot = true;
                                        } else break;
                                   }
                              }
                              if(k == line.size()) isnumber = true;
                              else printf(KR "\tWrong number. Try again :)\n" RESET);
                         } else printf(KR "\tWrong number. Try again :)\n" RESET);
                    } else std::cout << KR "\tNumbers must have maximum" << CY " 7 " KR << "characters. It's because it looks nicer :)\n" RESET << std::flush;
                    
               }

               A[i][j] = stod(line);
          }
     }
     return A;
}