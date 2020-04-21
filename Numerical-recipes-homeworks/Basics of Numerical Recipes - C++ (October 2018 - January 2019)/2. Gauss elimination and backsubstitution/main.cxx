#include <iostream>

double** genTriDiagMatrix(int n, int c) {
     double** matrix = new double*[n];

     for(int i = 0; i < n; i++) {
          matrix[i] = new double[n];
     }
     
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

     return matrix;
}

void gaussElimination(double **tab, double *res, int n) {
     for(int i = 0; i < n; i++) {
          double div = tab[i][i];

          for(int j = i; j < n; j++) {
               tab[i][j] /= div;
          }
          res[i] /= div;

          if(i+1 < n) {
               for(int k = i+1; k < n; k++) {
                    double mul = tab[i][i]*tab[k][i];
                    for(int j = i; j < n; j++) {
                         tab[k][j] -= mul*tab[i][j];
                    }
                    res[k] -= mul*res[i];
               }
          }
     }
}

void back_substitution(double **tab, double* res, int n) {

     for(int i = n-1; i > 0; i--) {
          for(int j = i-1; j>= 0; j--) {
               res[j] -= tab[j][i]*res[i];
          }
     }
}

double* genResults(int n) {
     double *res = new double[n];

     for(int i = 0; i < n; i++) {
          res[i] = i+1;
     }
     return res;
}

void printMatrix(double **tab, double* res, int n) {
     for(int i = 0; i < n; i++) {
          for(int j = 0; j < n; j++) {
               printf("%.1f ", tab[i][j]);
          }
          printf("| %.1f", res[i]);
          printf("\n");
     }
}

void printResults(double* res, int n) {
     for(int i = 0; i < n; i++) {
          printf("x%d = %.15f\n", i+1, res[i]);
     }
}

int main() {

     for(int i = 4; i <= 10; i++) {
          double **arr0 = genTriDiagMatrix(i, 0);
          double **arr1 = genTriDiagMatrix(i, 1);
          double *res0 = genResults(i);
          double *res1 = genResults(i);
          printMatrix(arr0, res0, i);
          gaussElimination(arr0, res0, i);
          back_substitution(arr0, res0, i);
          printResults(res0, i);

          printMatrix(arr1, res1, i);
          gaussElimination(arr1, res1, i);
          back_substitution(arr1, res1, i);
          printResults(res1, i);
     }     
     
     return 0;
}