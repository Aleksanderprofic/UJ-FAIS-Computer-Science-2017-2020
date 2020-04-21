/*********************************************************
*                        Zadanie 3
*                    Aleksander Profic
*********************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>            /* printf */
#include <sys/types.h>        /* semafory */
#include <sys/ipc.h>          /* semafory */
#include <sys/sem.h>          /* semafory */
#include <sys/wait.h>         /* wait */
#include <unistd.h>           /* fork */

#include "sem.h"

int main(int argc, char * argv[]) {
     
     /* sprawdzenie liczby argumentow */
     if(argc != 3) {
          perror("Liczba argumentow");
          exit(EXIT_FAILURE);
     }
     /* tworzenie zmiennych oraz semafora */
     int i, counter, semid = semDecl('A');
     /* inicjalizacja semafora */
     semInit(semid, 1);
     /* pomocnicza tablica dla argumentow programu */
     char * argu[2];
     
     /* alokowanie pamięci */
     for(i = 0; i < 2; i++) {
          argu[i] = malloc(strlen(argv[i+1])+1);
     }
     /* przekopiowanie argumentow programu do pomocniczej tablicy */
     for(i = 0; i < 2; i++) {
          strcpy(argu[i], argv[i+1]);
     }

     counter = atoi(argu[1]);
     printf("Rozpoczęcie tworzenia procesow.\n");
     semInfo2(semid);

     /* tworzenie procesow potomnych i uruchamianie programu prog.x */
     for(i = 0; i < counter; i++) {
          switch(fork()) {
               case -1:
                    perror("fork");
                    exit(EXIT_FAILURE);
                    break;
               case 0:
                    execl(argu[0], argu[0], NULL);
                    perror("execl");
                    exit(EXIT_FAILURE);
                    break;
               default:
                    break;
          }
     }

     /* czekanie na zakonczenie procesow */
     for(i = 0; i < counter; i++) {
          wait(NULL);
     }
     /* usuniecie semafora */
     semRm(semid);

     /* zwolnienie wcześniej zaalokowanej pamięci */
     for(i = 0; i < 2; i++) {
          free(argu[i]);
     }

     return 0;
}