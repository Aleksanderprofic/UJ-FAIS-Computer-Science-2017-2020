/*********************************************************
*                        Zadanie 3
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>      /* rand, exit */
#include <unistd.h>      /* usleep */
#include <time.h>        /* time */
#include <sys/sem.h>     /* semget */
#include "shmem.h"
#include "sem.h"

#define SIZE 10

typedef struct cykliczny {
     int size;
     char bufor[SIZE];
} cykliczny;

void konsument() {

     /* tworzenie zmiennych */
     FILE *fp;
     int c_cnt = 0, i = 0, semid, shmid;
     cykliczny * buf;
     char c;

     /* otwieranie pliku schowek.txt do zapisu */
     if((fp = fopen("./schowek.txt", "w")) == NULL) {
          perror("fopen konsument");
          exit(EXIT_FAILURE);
     }

     /* pobieranie id semaforow */
     semid = semDecl('A', 2);
     /* pobieranie id segmentu pamieci dzielonej */
     shmid = shmOpen('A');
     /* tworzenie dowiązania pamięci dzielonej */
     buf = (cykliczny *)shmAt(shmid);

     while(!((semctl(semid, 0, GETVAL) == SIZE) && (c_cnt == buf->size))) {

          /* opuszczenie semafora 1 */
          semP(semid, 1);

          /* zaczyna korzystać z pamięci dzielonej */

          usleep(rand()%5555);
          /* zapis znaku z pamieci dzielonej do zmiennej c */
          c = buf->bufor[i%SIZE];
          /* podniesienie semafora 0 */
          semV(semid, 0);

          /* przestaje korzystać z pamięci dzielonej */

          /* zapis znaku ze zmiennej c do pliku schowek.txt */
          fputc(c, fp);
          /* wypisanie zapisanego znaku na ekran */
          printf("Konsument << %c\n", c);
          /* inkrementacja */
          i++;
          c_cnt++;
     }

     /* zamkniecie pliku schowek.txt */
     if(fclose(fp) == EOF) {
          perror("fclose konsument");
          exit(EXIT_FAILURE);
     }
     /* usuniecie dowiazania pamieci dzielonej */
     shmDt(buf);
}

int main(int argc, char * argv[]) {

     /* sprawdza ilość zargumentow */
     if(argc != 1) {
          perror("Liczba argumentow konsument.x");
          exit(EXIT_FAILURE);
     }

     /* zarodek dla randa */
     srand(time(NULL));

     konsument();

     return 0;
}