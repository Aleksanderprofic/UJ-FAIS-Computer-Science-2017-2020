#include <iostream>
#include "stack.hpp"

int maxAreaWithStack(char* A[], int ymax, int xmax) {
     Stack<int> stack(xmax);
     Stack<int> heights(xmax);

     int pom[xmax], maxArea = 0, area = 0, top = 0, h = 0;

     // Wypełnienie pomocniczej tablicy pierwszym wierszem macierzy A
     for(int j = 0; j < xmax; j++) {
          pom[j] = 0;
     }
     int j = 0, i = 0;

     for(i = 0; i < ymax; i++) {
          for(j = 0; j < xmax; j++) {
               if(A[i][j] == '1') {
                    pom[j]++;

                    if(stack.empty() || heights.top() <= pom[j]) {
                         stack.push(j);
                         heights.push(pom[j]);
                    } else {
                         do {
                              top = stack.pop();
                              h = heights.pop();
                              area = h*(j-top);
                              if(area > maxArea) maxArea = area;
                         } while(!heights.empty() && heights.top() > pom[j]);

                         if(heights.empty()) {
                              stack.push(top);
                              heights.push(pom[j]);
                         } else {
                              if(heights.top() < pom[j]) {
                                   stack.push(top);
                                   heights.push(pom[j]);
                              }
                         }
                    }
               } else {
                    pom[j] = 0;

                    while(!stack.empty()) {
                         top = stack.pop();
                         h = heights.pop();
                         area = h*(j-top);
                         if(area > maxArea) maxArea = area;
                    }
               }
          }
          while(!stack.empty()) {
               top = stack.pop();
               h = heights.pop();
               area = h*(j-top);
               if(area > maxArea) maxArea = area;
          }
     }
     return maxArea;
}

bool isValid(char* A[], int xFrom, int xTo, int yFrom, int yTo){
     for(int i = yFrom; i <= yTo; i++){
          for(int j = xFrom; j <= xTo; j++){
               if(A[i][j] != '1') return false;
          }
     }
     return true;
}

int getArea(int xFrom, int xTo, int yFrom, int yTo){
     return (xTo - xFrom + 1) * (yTo - yFrom + 1);
}

int maxAreaBruteForce(char* A[], int ymax, int xmax) {
     int maxArea = 0;
     for(int yFrom = 0; yFrom < ymax; yFrom++) {
          for(int yTo = yFrom; yTo < ymax; yTo++) {
               for(int xFrom = 0; xFrom < xmax; xFrom++) {
                    for(int xTo = xFrom; xTo < xmax; xTo++) {
                         if(isValid(A, xFrom, xTo, yFrom, yTo)) {
                              maxArea = std::max(maxArea, getArea(xFrom, xTo, yFrom, yTo));
                         }
                    }
               }
          }
     }
     return maxArea;
}

int main(int argc, char* argv[]) {
     if(argc < 3) {
          std::cerr << "Not enough arguments. Enter sizes of N and M" << std::endl;
          exit(-1);
     }

     const int N = atoi(argv[1]);
     const int M = atoi(argv[2]);

     char* A[N];
     

     for(int i = 0; i < M; i++) {
          A[i] = new char[M];
     }


     for(int i = 0; i < N; i++) {
          for(int j = 0; j < M; j++) {
               std::cin >> A[i][j];
          }
     }

     std::cout << "Matrix looks like this: " << std::endl;
     for(int i = 0; i < N; i++) {
          for(int j = 0; j < M; j++) {
               std::cout << A[i][j] << " " << std::flush;
          }
          std::cout << std::endl;
     }

     int max = maxAreaWithStack(A, N, M);
     int max2 = maxAreaBruteForce(A, N, M);

     std::cout << "Najwieksze pole prostokata wynosi: " << max << std::endl;
     std::cout << "Najwieksze pole prostokata wynosi wg brute-force: " << max2 << std::endl;
}