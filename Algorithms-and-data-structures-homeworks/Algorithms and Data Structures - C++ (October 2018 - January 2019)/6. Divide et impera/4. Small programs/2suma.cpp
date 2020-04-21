#include <iostream>
#include <random>

bool searchSum(int A[], int nA, int B[], int nB, int x) {
     int temp = 0, i = 0, j = nB - 1;
     while(i < nA && j >= 0) {
          if((temp = A[i] + B[j]) == x) return true;
          else if (temp < x) {
               i++;
          } else {
               j--;
          }
     }
     return false;
}

int main(int argc, char* argv[]) {

     if(argc < 3) {
          std::cout << "Not enough arguments" << std::endl;
          exit(-1);
     }

     int nA = atoi(argv[1]);
     int nB = atoi(argv[2]);

     std::random_device rd;
     std::default_random_engine generator{rd()};
     std::uniform_int_distribution<int> distribution(-1000, 1000);

     int A[nA], B[nB];

     for(int i = 0; i < nA; i++) {
          A[i] = distribution(generator);
     }

     for(int i = 0; i < nB; i++) {
          B[i] = distribution(generator);
     }

     std::sort(A, A+nA);
     std::sort(B, B+nB);

     std::cout << "Tablica A:" << std::endl;
     for(int i = 0; i < nA; i++) {
          std::cout << A[i] << std::endl;
     }

     std::cout << "Tablica B:" << std::endl;
     for(int i = 0; i < nB; i++) {
          std::cout << B[i] << std::endl;
     }

     if(searchSum(A, nA, B, nB, 400)) {
          std::cout << "Istnieją takie a i b" << std::endl;
     } else {
          std::cout << "Nie istnieją takie liczby" << std::endl;
     }
}