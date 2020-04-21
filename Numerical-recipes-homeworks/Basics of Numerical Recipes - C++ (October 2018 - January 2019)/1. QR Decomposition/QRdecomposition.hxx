#pragma once

#include <iostream>
#include <cmath>
#include <vector>

double computeNorm(std::vector<double>& a) {
     double sum = 0;
     for(int i = 0; i < a.size(); i++) {
          sum += pow(a[i],2);
     }

     return sqrt(sum);
}

std::vector<double>& subVector(std::vector<double>& a, std::vector<double>& b) {
     if(a.size() == b.size()) {
          for(int i = 0; i < a.size(); i++) {
               a[i] -= b[i];
          }
          return a;
     } else {
          std::cout << "Unable to sub Vectors. Sizes are not equal." << std::endl;
          exit(-1);
     }
}

double scalarProduct(const std::vector<double>& a, std::vector<double>& b) {
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

std::vector<double> multiplyByScalar(std::vector<double>& a, double scalar) {
     std::vector<double> T(a.size());
     for(int i = 0; i < a.size(); i++) {
               T[i] = a[i] * scalar;
     }  
     return move(T);
}

void multiply(std::vector<std::vector<double> >& a, const std::vector<std::vector<double> >& r, std::vector<std::vector<double> >& q) {
     int size;
     if((size = r.size()) != q.size()) {
          std::cout << "Unable to multiply. Sizes are not equal." << std::endl;
          exit(-1);
     } else {
          for(int i = 0; i < size; i++) {
               for(int j = 0; j < size; j++) {
                    a[i][j] = scalarProduct(r[i],q[j]);
               }
          } 
     }
}

void QRdecomposition(const std::vector<std::vector<double> >& A, 
                           std::vector<std::vector<double> >& Q, 
                           std::vector<std::vector<double> >& R) {

     
     for(int i = 0; i < A[0].size(); i++) {
          std::vector<double> u = A[i];

          double scalar = 0;
          for(int j = 0; j < i; j++) {
               scalar = scalarProduct(A[i], Q[j]);
               std::vector<double> mul = multiplyByScalar(Q[j], scalar);
               u = subVector(u, mul);
          }

          u = multiplyByScalar(u, (1/(computeNorm(u))) );

          for(int j = 0; j < u.size(); j++) {
               Q[i][j] = u[j];
          }

          for(int j = i; j < u.size(); j++) {
               R[i][j] = scalarProduct(A[j],Q[i]);
          }
     }
}