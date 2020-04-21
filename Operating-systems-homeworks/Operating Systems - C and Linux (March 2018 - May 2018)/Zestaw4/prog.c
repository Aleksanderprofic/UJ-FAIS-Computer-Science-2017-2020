/*********************************************************
*                        Zadanie 3
*                    Aleksander Profic
*********************************************************/

#include <stdlib.h>           /* rand */
#include <string.h>
#include <stdio.h>            /* printf */
#include <sys/types.h>        /* semafory */
#include <sys/ipc.h>          /* semafory */
#include <sys/sem.h>          /* semafory */
#include <unistd.h>           /* usleep */
#include <time.h>             /* time */
#include "sem.h"

int main(int argc, char * argv[]) {

     /* sprawdzenie liczby argumentow */
     if(argc != 1) {
          perror("Liczba argumentow");
          exit(EXIT_FAILURE);
     }

     /* tworzenie zmiennych */
     int pid, i;

     /* zarodek dla randa */
     srand(time(NULL));

     /* uzyskanie id procesu */
     pid = getpid();

     /* uzyskanie id semafora */
     int semid = semDecl('A');

     for(i = 0; i < 3; i++) {

          /* przed sekcja krytyczna */
          printf("\n----> PROCES %d PRZED SEKCJA KRYTYCZNA\n", pid);
          semInfo2(semid);
          semP(semid);   /* opuszczenie semafora */
          usleep(rand()%3333333);

          /* w sekcji krytycznej */
          printf("\n----> PROCES %d W SEKCJI KRYTYCZNEJ <----\n", pid);
          semInfo2(semid);
          usleep(rand()%3333333);

          /* po sekcji krytycznej */
          semV(semid);   /* podniesienie semafora */
          printf("\nPROCES %d PO SEKCJI KRYTYCZNEJ <----\n", pid);
          semInfo2(semid);   
          usleep(rand()%3333333);
     }    

     return 0;
}