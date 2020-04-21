/*********************************************************
*                   Program do zadania 2
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>           /* exit, rand */
#include <unistd.h>           /* fork, pipe, write, read, usleep */
#include <sys/types.h>        /* wait, mkfifo, open */
#include <sys/wait.h>         /* wait */
#include <sys/stat.h>         /* open */
#include <time.h>             /* time */
#include <fcntl.h>            /* open */

#define SIZE 20

char buf[SIZE];

int usleep();

void producent(const char * fifo) {
     FILE *fp;
     int fd;

/* otwarcie pliku magazyn.txt */
     fp = fopen("./magazyn.txt", "r");
/* otwarcie potoku do zapisu */
     fd = open(fifo, O_WRONLY);
/* dopóki nie dojdziemy do końca pliku to pętla będzie się wykonywać */
     while(!feof(fp)) {
/* uśpienie programu na losową ilość sekund */
          usleep(rand()%1111111);
/* czytanie danych z pliku wskazywanego przez fp i zapisywanie do buf */
          if(fgets(buf, SIZE, fp) == buf) {
/* przesyłanie danych z buf przez potok fifo i obsługa błędów */
          if(write(fd, buf, SIZE) == -1) {
               perror("Blad write");
               exit(EXIT_FAILURE);
          }
          printf("Producent >>>>> %s\n", buf);
          }
     }
/* zamknięcie deskryptora potoku */
     if(close(fd) == -1) {
         perror("Blad close producent");
         exit(EXIT_FAILURE);
    }
/* zamknięcie pliku magazyn.txt */
     if(fclose(fp) == EOF) {
          perror("Blad fclose producent");
          exit(EXIT_FAILURE);
     }
}

int main(int argc, char * argv[]) {
/* obsługa błędów przy złej ilości argumentów */
     if(argc != 2) {
          perror("Blad liczba arg producent");
          exit(EXIT_FAILURE);
     }
/* wywołanie funkcji producent() */
     producent(argv[1]);

     return 0;
}
