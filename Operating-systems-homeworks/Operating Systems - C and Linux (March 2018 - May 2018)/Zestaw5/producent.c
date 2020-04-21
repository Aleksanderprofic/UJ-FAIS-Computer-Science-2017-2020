/*********************************************************
*                        Zadanie 3
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>      /* rand, exit */
#include <unistd.h>      /* usleep */
#include <time.h>        /* time */
#include "shmem.h"
#include "sem.h"

#define SIZE 10

typedef struct cykliczny {
     int size;
     char bufor[SIZE];
} cykliczny;

void producent() {

     /* tworzenie zmiennych */
     FILE *fp;
     int i, semid, shmid;
     cykliczny * buf;
     char c;

     /* otwieranie pliku magazyn.txt do odczytu */
     if((fp = fopen("./magazyn.txt", "r")) == NULL) {
          perror("fopen producent");
          exit(EXIT_FAILURE);
     }

     /* pobieranie id semaforow */
     semid = semDecl('A', 2);
     /* pobieranie id segmentu pamieci dzielonej */
     shmid = shmOpen('A');
     /* tworzenie dowiązania pamięci dzielonej */
     buf = (cykliczny *)shmAt(shmid);

     /* pętla działa dopoki fgetc nie zwroci konca pliku, pobiera znak z magazyn.txt i zapisuje do zmiennej c */
     for(i = 0; (c = fgetc(fp)) != EOF; i++) {
          
          /* opuszczenie semafora 0 */
          semP(semid, 0);
          /* zaczyna korzystać z pamięci dzielonej */

          usleep(rand()%5555);
          /* zapisanie znaku c w pamięci dzielonej */
          buf->bufor[i%SIZE] = c;
          /* zwiekszenie o 1 licznika ilości znakow zapisanych w pamieci dzielonej */
          buf->size++;
                                   
          /* podniesienie semafora 1 */
          semV(semid, 1);

          /* przestaje korzystać z pamięci dzielonej */

          /* wypisanie na ekran znaku zapisanego w pamięci dzielonej */
          printf("Producent >> %c\n", c);
     }

     /* zamkniecie pliku magazyn.txt */
     if(fclose(fp) == EOF) {
          perror("fclose producent");
          exit(EXIT_FAILURE);
     }
     /* usuniecie dowiazania segmentu pamięci dzielonej */
     shmDt(buf);
}


int main(int argc, char * argv[]) {

     /* sprawdza ilość argumentow */
     if(argc != 1) {
          perror("Liczba argumentow producent.x");
          exit(EXIT_FAILURE);
     }

     /* zarodek dla randa */
     srand(time(NULL));

     producent();     

     return 0;
}