#include <cmath>
#include "QRdecomposition.hxx"

std::vector<std::vector<double> > genMatrix(int n, bool elements = false, int c=0) {
     std::vector<std::vector<double> > matrix(n);

     for(int i = 0; i < n; i++) {
          matrix[i].resize(n);
     }

     if(elements) {

          for(int i = 0; i < n; i++) {
               for(int j = 0; j < n; j++) {
                    matrix[i][j] = 0;
               }
          }
          
          matrix[0][0] = 6;
          matrix[1][0] = 1;
          matrix[n-1][0] = c;
          matrix[n-1][n-1] = 6;
          matrix[n-2][n-1] = 1;
          matrix[0][n-1] = c;

          for(int i = 1; i < n-1; i++) {
               matrix[i][i] = 6;
               matrix[i+1][i] = 1;
               matrix[i-1][i] = 1;
          }
     } else {
          for(int i = 0; i < n; i++) {
               for(int j = 0; j < n; j++) {
                    matrix[i][j] = 0;
               }
          }
     }

     return move(matrix);
}

constexpr int n = 4;

int main() {

     std::vector<std::vector<double> > A = genMatrix(n, true, 1);
     
     std::vector<std::vector<double> > Q = genMatrix(n);
     
     std::vector<std::vector<double> > R = genMatrix(n);

     for(int i = 0; i < n; i++) {
          for(int j = 0; j < n; j++) {
               printf("%.10f\t", A[i][j]);
          }
          printf("\n");
     }

     for(int i = 1; i < 1000; i++) {
          QRdecomposition(A, Q, R);
          multiply(A, R, Q);    
     }
     
     printf("\n[   ");
          for(int i = 0; i < n; i++) {
               printf("%.10f   ", A[i][i]);
          }
     printf("]\n");
     return 0;
}