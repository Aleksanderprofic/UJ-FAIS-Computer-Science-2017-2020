/*********************************************************
*                Zadanie - Algorytm piekarni
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>      /* exit, atoi */
#include <unistd.h>      /* sleep */

#include "shmem.h"

/* liczba utworzonych procesow */
#define P_NR 5

#define true 1
#define false 0

typedef struct shared {
     volatile int counter;
     volatile int num[P_NR];
     volatile int choosing[P_NR];
} sharedMem;

/* funkcja zwracająca max wartość */
volatile int maxvalue(volatile int tab[], int size) {
     volatile int i, max = 0;

     for(i = 0; i < size; i++) {
          if(max < tab[i]) max = tab[i];
     }
     return max;
}

/* funkcja do obsługi sygnałow */
void signal_handler(int nr_syg) {
     printf("Sygnal %d zostal obsluzony przez proces o id: %d\n", nr_syg, getpid());
     exit(EXIT_SUCCESS);
}

void proces(int k) {

     /* tworzenie zmiennych */
     int shmid, j;
     sharedMem * shm;

     /* uzyskiwanie dostępu do pamięci dzielonej */
     shmid = shmOpen('B');

     /* tworzenie dowiązania do pamięci dzielonej */
     shm = (sharedMem *)shmAt(shmid);

     do {

     /* przydzielanie numerku procesowi */

          shm->choosing[k] = true;
          shm->num[k] = maxvalue(shm->num,P_NR) + 1;
          shm->choosing[k] = false;

     /* koniec przydzielania numerku */
          
          /* pętla zezwalająca na dostęp do sekcji krytycznej */
          for(j = 0; j < P_NR; j++) { 
               while(shm->choosing[j] == true);
               while((shm->num[j] != 0) && ( ( shm->num[j] < shm->num[k] ) || (( shm->num[j] == shm->num[k] ) && (j < k) )));
          }

          /* SEKCJA KRYTYCZNA */
          printf("\033[%d;0H                                       \n\033[0m", k+3);
          /* wypisywanie po prawej stronie ekranu */
          printf("\033[%d;80H\033[31mCRITICAL section of process nr %d\n\033[0m", k+3, k);

          sleep(2);
          printf("\033[%d;80H                                       \n\033[0m", k+3);
          /* wypisywanie po lewej stronie ekranu */
          printf("\033[%d;0H\033[32mPRIVATE section of process nr %d\n", k+3, k);
          /* KONIEC SEKCJI KRYTYCZNEJ */
          shm->num[k] = 0;

     } while(true);
}

int main(int argc, char * argv[]) {

     /* sprawdzenie ilości argumentow */
     if(argc != 2) {
          perror("Number of arguments");
          exit(EXIT_FAILURE);
     }

     /* przygotowanie funkcji na przyjecie sygnału */
     if(signal(2, signal_handler) == SIG_ERR) {
          printf("Funkcja signal ma problem z sygnalem SIGINT");
     }

     /* k - nr procesu */
     int k = atoi(argv[1]);
     
     proces(k);

     return 0;
}