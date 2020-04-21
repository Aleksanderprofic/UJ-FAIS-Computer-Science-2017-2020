#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printArray(int * array, int n) {
     for(int i = 0; i < n; i++) {
          printf("%d\n", array[i]);
     }
}

int compareFunction(const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}

int main(int argc, char* argv[]) {

     int size;

     if(argc == 1) size = 10000;
     else if(argc == 2) {
          size = atoi(argv[1]);
     } else {
          printf("Too much arguments");
          return 1;
     }

     int array[size];

     for(int i = 0; i < size; i++) {
          int numberEntered;
          //cout << "Enter " << i+1 << " number: " << flush;
          scanf("%d ", &numberEntered);
          array[i] = numberEntered;
     }

     //cout << "Before sorting: " << endl;
     //printArray(array, size);
     clock_t end;
     clock_t start = clock();
     
     qsort(array, size, sizeof(int), compareFunction);
     
     end = clock();

     double difference = (double)(end - start)/CLOCKS_PER_SEC;

     //printf("qsort time for %d elements: %f\n", size, difference);

     //cout << "After sorting: " << endl;
     printArray(array, size);

     return 0;
}