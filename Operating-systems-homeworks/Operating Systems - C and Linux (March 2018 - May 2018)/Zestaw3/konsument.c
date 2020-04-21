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

void konsument(const char * fifo) {
     FILE *fp;
     int fd;
     ssize_t ret_read;
/* otwarcie pliku schowek.txt */
     fp = fopen("./schowek.txt", "w");
/* utworzenie deskryptora potoku */
     fd = open(fifo, O_RDONLY);
/* czytanie z deskryptora dopóki funkcja read zwraca niezerową, dodatnią ilość bajtów */
    while((ret_read = read(fd, buf, SIZE)) > 0) {
/* uśpienie programu na losową ilość sekund */
         usleep(rand()%1111111);
/* zapisywanie danych z bufora do pliku schowek.txt */
         if(fputs(buf, fp) < 0) {
              perror("Blad fputs");
              exit(EXIT_FAILURE);
         }
    printf("Konsument <<< %s\n", buf);
    }
/* jeśli czytanie danych zakończy sie niepowodzeniem */
    if(ret_read == -1) {
         perror("Blad read");
         exit(EXIT_FAILURE);
    }
/* zamknięcie deskryptora potoku */
    if(close(fd) == -1) {
         perror("Blad close konsument");
    }
/* zamknięcie pliku schowek.txt */
    if(fclose(fp) == EOF) {
         perror("Blad fclose konsument");
         exit(EXIT_FAILURE);
    }
}


int main(int argc, char * argv[]) {
/* obsługa błędów przy złej ilości argumentów */
     if(argc != 2) {
          perror("Blad liczba arg konsument");
          exit(EXIT_FAILURE);
     }
/* wywołanie funkcji konsument() */
     konsument(argv[1]);

     return 0;
}
