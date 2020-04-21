#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

/* kolory w terminalu */

#define KY "\x1B[33m"   /* zolty */
#define CY "\x1B[36m"   /* jasny niebieski */
#define RESET "\x1B[0m" /* powrot do normalnego koloru */

constexpr double epsilon = 1e-15;

// Oblicza norme wektora
double computeNorm(std::vector<double> a) {
     double sum = 0;
     for(int i = 0; i < a.size(); i++) {
          sum += pow(a[i],2);
     }

     return sqrt(sum);
}

// Odejmuje wektor b od wektora a
std::vector<double> subvector(std::vector<double>& a, std::vector<double> b) {
     std::vector<double> temp(a.size());
     if(a.size() == b.size()) {
          for(int i = 0; i < a.size(); i++) {
               temp[i] = a[i] - b[i];
          }
          return temp;
     } else {
          std::cout << "Unable to sub std::vectors. Sizes are not equal." << std::endl;
          exit(-1);
     }
}

// Oblicza iloczyn skalarny wektorow a i b
double scalarProduct(const std::vector<double> a, std::vector<double> b) {
     int size;
     if((size = a.size()) != b.size()) {
          std::cout << "Unable to compute scalarProduct. Sizes are not equal." << std::endl;
          exit(-1);
     } else {
          double product = 0;
          for(int i = 0; i < size; i++) {
               product += a[i]*b[i];
          }
          return product;
     }
}

// Mnozenie wektora przez liczbę
void multiplyVectorByScalar(std::vector<double>& a, double scalar) {
     for(int i = 0; i < a.size(); i++) {
               a[i] *= scalar;
     }  
}

// Mnozenie wektora przez liczbę
std::vector<double> multiplyVectorByScalarAndReturn(std::vector<double>& a, double scalar) {
     std::vector<double> temp(a.size());
     for(int i = 0; i < a.size(); i++) {
               temp[i] = a[i] * scalar;
     }  

     return temp;
}

void multiplyMatrixByScalar(std::vector<std::vector<double> >& a, double scalar) {
     for(int i = 0; i < a.size(); i++) {
          for(int j = 0; j < a[i].size(); j++) {
               a[i][j] *= scalar;
          }
     }
}

// Mnozenie macierzy A przez wektor
std::vector<double> multiplyMatrixByVector(const std::vector<std::vector<double> >& A, const std::vector<double>& vect) {
     int n;
     if((n = A.size()) != vect.size()) {
          std::cout << "\tUnable to multiply. Dimensions are not equal." << std::endl;
          exit(-1);
     } else {
          std::vector<double> temp(n);
          for(int i = 0; i < n; i++) {
               temp[i] = 0;
               for(int j = 0; j < n; j++) {
                    temp[i] += A[i][j] * vect[j];
               }
          }
          
          return temp;
     }
}

void normalizeVector(std::vector<double>& vect) {
     double norm = computeNorm(vect);
     multiplyVectorByScalar(vect, 1/norm);
}

// Zwraca wektor prostopadły do wektora podanego w argumencie
std::vector<double> perpendicularVector(std::vector<double> vector) {
     int size = vector.size();
     std::vector<double> temp(size);
     double sum = 0;
     for(int i = 0; i < size-1; i++) {
          temp[i] = (rand()%100+1);
          sum += temp[i]*vector[i]; 
     }

     temp[size-1] = -sum/vector[size-1];
     return temp;
}


// Generowanie losowego wektora o długości 1
std::vector<double> genNormalizeRandomVector(int dimensions) {
     if(dimensions > 0) {
          std::vector<double> vector;

          for(int i = 0; i < dimensions; i++) {
               vector.push_back(rand()%10+1);
          }
          normalizeVector(vector);

          return vector;
     } else {
          std::cerr << "Dimensions cannot be less than 1" << std::endl;
          exit(-1);
     }
}

void printMatrix(const std::vector<std::vector<double> >& A) {
     int n = A.size();
     for(int i = 0; i < n; i++) { 
          for(int j = 0; j < A[i].size(); j++) {
               double temp = A[i][j];
               if((temp > -1000000 && temp <= -10000) || (temp >= 100000 && temp < 10000000)) printf("%.0f\t", temp);
               else if((temp > -10000 && temp <= -1000) || (temp >= 10000 && temp < 100000)) printf("%.1f\t", temp);
               else if((temp > -1000 && temp <= -100) || (temp >= 1000 && temp < 10000)) printf("%.2f\t", temp);
               else if((temp > -100 && temp <= -10) || (temp >= 100 && temp < 1000)) printf("%.3f\t", temp);
               else if((temp > -10 && temp < 0) || (temp >= 10 && temp < 100)) printf("%.4f\t", temp);
               else if(temp >= 0 && temp < 10) printf("%.5f\t", temp);
          }
          printf("\n");
     }
}

// Wypisuje wektor
void printVector(const std::vector<double>& v) {
     printf(KY "[ ");
     for(int i = 0; i < v.size(); i++) {
          printf("%.18f ", v[i]);
     }
     printf("]\n" RESET);
}

void powerIteration(std::vector<std::vector<double> >& A, std::vector<double> y_k ) {
     std::vector<double> z_k;
     double lambda1, lambda2;
     std::vector<double> v1, v2, difference, z_kNotNormed;

     // Wiodąca wartość i wektor własny
     do {
          z_k = multiplyMatrixByVector(A, y_k);
          z_kNotNormed = z_k;
          normalizeVector(z_k);
          difference = subvector(y_k, z_k);
          
          y_k = z_k;
     } while(computeNorm(difference) >= epsilon);

     // Wiodąca wartość i wektor własny
     lambda1 = computeNorm(z_kNotNormed);
     v1 = z_k;

     // Wektor prostopadły do wyliczonego wcześniej wektora v1
     y_k = perpendicularVector(v1);

     // Metoda potęgowa dla pod wiodącej wartości i wektora własnego
     do {
          z_k = multiplyMatrixByVector(A, y_k);
          z_k = subvector(z_k, multiplyVectorByScalarAndReturn(v1, scalarProduct(v1, z_k)));

          z_kNotNormed = z_k;

          // Teraz y_k+1 = z_k
          normalizeVector(z_k);
          difference = subvector(y_k, z_k);
          
          y_k = z_k;
     } while(computeNorm(difference) >= epsilon);

     // Pod wiodąca wartość i wektor własny
     lambda2 = computeNorm(z_kNotNormed);
     v2 = z_k;


     printf("Wiodąca wartość własna -> Lambda1: \n" CY "%.18f\n" RESET, lambda1);
     printf("Wiodący wektor własny -> v1: \n");
     printVector(v1);
     printf("Pod wiodąca wartość własna -> Lambda2: \n" CY "%.18f\n" RESET, lambda2);
     printf("Pod wiodący wektor własny -> v2: \n");
     printVector(v2);
}

int main() {
     srand(time(NULL));

     std::vector<std::vector<double> > A = { {19, 13, 10, 10, 13, -17},
                                             {13, 13, 10, 10, -11, 13}, 
                                             {10, 10, 10, -2, 10, 10},
                                             {10, 10, -2, 10, 10, 10},
                                             {13, -11, 10, 10, 13, 13},
                                             {-17, 13, 10, 10, 13, 19} };
     double scalar = 1./12;
     printf("Macierz A:\n");
     printMatrix(A);

     printf("\n");

     multiplyMatrixByScalar(A, scalar);

     // Obliczanie wiodących i pod wiodących wartości i wektorow własnych macierzy A
     powerIteration(A, genNormalizeRandomVector(6));

     return 0;
}