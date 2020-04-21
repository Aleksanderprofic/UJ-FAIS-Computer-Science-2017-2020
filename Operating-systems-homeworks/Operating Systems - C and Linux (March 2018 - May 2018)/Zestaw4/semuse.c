/*********************************************************
*                        Zadanie 2
*                    Aleksander Profic
*********************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>            /* printf */
#include <sys/types.h>        /* semafory */
#include <sys/ipc.h>          /* semafory */
#include <sys/sem.h>          /* semafory */
#include "sem.h"

int main(int argc, char * argv[]) {
     /* sprawdza liczbe argumentow */
     if(argc != 2) {
          perror("Liczba argumentow");
          exit(EXIT_FAILURE);
     }

     /* sprawdza dlugosc argumentu 1 */
     if(strlen(argv[1]) != 1) {
          perror("Dlugosc argumentu 1");
          exit(EXIT_FAILURE);
     }

     /* stworzenie semafora */
     int semid = semDecl('A');

     /* głowna obsługa programu */
     switch(argv[1][0]) {
          case 'i':
               /* inicjalizacja semafora */
               semInit(semid, 3);
               semInfo(semid);
               break;
          case 'r':
               /* usuwanie semafora */
               semRm(semid);
               break;
          case 'p':
               /* opuszczenie semafora */
               semP(semid);
               semInfo(semid);
               break;
          case 'v':
               /* podniesienie semafora */
               semV(semid);
               semInfo(semid);
               break;
          case 'z':
               /* czeka na wyzerowanie semafora */
               semZ(semid);
               semInfo(semid);
               break;
          case 'q':
               /* informacje o semaforze */
               semInfo(semid);
               break;
          default:
               printf("Bledny argument programu\n");
               break;
     }
     
     return 0;
}