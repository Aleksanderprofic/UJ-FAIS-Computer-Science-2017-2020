/*********************************************************
*                        Zadanie 3
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <unistd.h>      /* fork */
#include <stdlib.h>      /* exit */
#include "sem.h"
#include "shmem.h"

#define SIZE 10

typedef struct cykliczny {
     int size;
     char bufor[SIZE];
} cykliczny;

int main(int argc, char * argv[]) {

     /* sprawdza ilość argumentow */
     if(argc != 1) {
          perror("Liczba argumentow");
          exit(EXIT_FAILURE);
     }
     /* tworzy zmienne dla semafora i pamieci dzielonej */
     int semid, shmid;

     /* tworzy 2 semafory */
     semid = semDecl('A', 2);
     /* inicjalizuje semafor 0 wartością SIZE*/
     semInit(semid, 0, SIZE);
     /* inicjalizuje semafor 1 wartością 0*/
     semInit(semid, 1, 0);

     /* tworzy pamięć dzieloną */
     shmid = shmCreate('A', sizeof(cykliczny));

     /* tworzy proces potomny producent.x */
     switch(fork()) {
          case -1:
               perror("fork 1");
               exit(EXIT_FAILURE);
               break;
          case 0:
               execl("./producent.x", "./producent.x", NULL);
               perror("execl p");
               exit(EXIT_FAILURE);
               break;
          default:
               break;
     }

     /* uśpienie na 1 sekundę, aby pętla while w procesie konsumenta zaczęła działać, 
     * poniewaz czasami działo się tak, ze konsument się zawieszał */
     sleep(1);
     
     /* tworzy proces potomny konsument.x */
     switch(fork()) {
          case -1:
               perror("fork 2");
               exit(EXIT_FAILURE);
               break;
          case 0:
               execl("./konsument.x", "./konsument.x", NULL);
               perror("execl k");
               exit(EXIT_FAILURE);
               break;
          default:
               break;
     }

     /* proces macierzysty czeka na 2 procesy potomne */
     wait(NULL);
     wait(NULL);

     /* usuniecie semaforow */
     semRm(semid, 2);
     /* usuniecie segmentu pamieci dzielonej */
     shmRm(shmid);

     /* sprawdza czy pliki magazyn.txt i schowek.txt sa takie same */
     system("diff -s magazyn.txt schowek.txt");

     return 0;
}