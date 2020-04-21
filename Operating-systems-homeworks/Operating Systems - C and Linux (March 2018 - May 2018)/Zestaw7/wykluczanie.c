#define _REENTRANT
#include <pthread.h>          /* wątki */
#include <stdlib.h>           /* exit */
#include <stdio.h>
#include <unistd.h>           /* sleep */

/* tutaj mozna zmienić ilość tworzonych wątkow i liczbe powtorzen w pętli */
#define THR_NR 6
#define LOOPS_NR 4

/*
Przesuniecie kursora do pozycji x, y na ekranie konsoli: \033[x;yH
Włącz normalny tekst:  \033[0m
Włącz pogrubienie tekstu:  \033[1m
Włącz podkreślenie tekstu:  \033[4m
Włącz migający tekstu:  \033[5m
Włącz inwersje tekstu:  \033[7m
Zmiana koloru tekstu: \033[xm
Zamiast symbolu x należy wstawić liczbę między 30 a 49.
Wyczyszczenie ekranu: \033c
*/

volatile unsigned int globalCounter = 0;

/* zainicjowanie mutexa wartością 0 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * threadMutex(void * data) {

     int localCounter, i;

     /* data to przekazywany argumentem funkcji nr watku, wykorzystywany do prawidlowego wypisywania na ekranie */
     int * j = (int *)data;
     
     /* zwraca nr wątku */
     

     for(i = 0; i < LOOPS_NR; i++) {

          /* wypisywanie po lewej stronie ekranu */
          printf("\033[%d;0H\033[32mPRIVATE section of thread: %d...\n\033[0m", *j+3, *j);
          
          /* zamkniecie muteksu */
          if(pthread_mutex_lock(&mutex) != 0) {
               perror("threadMutex mutex lock");
               exit(EXIT_FAILURE);
          }

          printf("\033[%d;0H\033[32m                                             \n\033[0m", *j+3);
          /* wypisywanie po prawej stronie ekranu */
          printf("\033[%d;89H\033[31mCRITICAL section of thread: %d...\n\033[0m", *j+3, *j);
          
          /* przypisanie globalnej zmiennej do zmiennej lokalnej */
          localCounter = globalCounter;
          /* inkrementacja lokalnej zmiennej */
          ++localCounter;

          sleep(2);

          /* przypisanie lokalnej zmiennej do zmiennej globalnej */
          globalCounter = localCounter;

          /* otwarcie muteksu */
          if(pthread_mutex_unlock(&mutex) != 0) {
               perror("threadMutex mutex unlock");
               exit(EXIT_FAILURE);
          }
          printf("\033[%d;89H\033[31m                                                             \n\033[0m", *j+3);
     }

     return data;
}

int main(int argc, char * argv[]) {

     /* sprawdzenie ilości argumentow */
     if(argc != 1) {
          perror("Number of arguments");
          exit(EXIT_FAILURE);
     }

     /* wyczyszczenie ekranu */
     printf("\033c");

     int i, j[THR_NR];
     pthread_t thrid[THR_NR];

     printf("\n\033[35mValue of the global counter at the start: %d\033[0m", globalCounter);
     
     /* tworzenie THR_NR wątkow */
     for(i = 0; i < THR_NR; i++) {
          j[i] = i+1;
          if(pthread_create(&thrid[i], NULL, threadMutex, &j[i]) != 0) {
               perror("main pthread create");
               exit(EXIT_FAILURE);
          }
     }

     /* czekanie na zakonczenie wątkow */
     for(i = 0; i < THR_NR; i++) {
          if (pthread_join(thrid[i], NULL) != 0) {
               perror("main pthread join");
               exit(EXIT_FAILURE);
          }
     }

     printf("\n\n\033[35mValue of the global counter at the end: %d\033[0m\n", globalCounter);

     /* usuwanie mutexu - mutex staje się niezainicjowany */
     if(pthread_mutex_destroy(&mutex) != 0) {
          perror("main pthread mutex destroy");
          exit(EXIT_FAILURE);
     }

     return 0;
}