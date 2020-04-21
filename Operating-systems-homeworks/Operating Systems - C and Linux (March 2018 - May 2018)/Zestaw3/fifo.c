/*********************************************************
*                        Zadanie 2
*                    Aleksander Profic
*********************************************************/


#include <stdio.h>
#include <stdlib.h>         /* exit, rand, system */
#include <unistd.h>         /* fork, pipe, write, read, usleep */
#include <sys/types.h>        /* wait, mkfifo, open */
#include <sys/wait.h>         /* wait */
#include <sys/stat.h>         /* mkfifo, open */
#include <time.h>             /* time */

int main(int argc, char * argv[]) {

/* tworzymy zmienną, która przechowuje nazwe potoku */
     const char * fifo;

/* domyślna wartosc fifo jezeli uzytkownik nie poda argumentu */
     if(argc == 1) {
          fifo = "fifo";
     }
/* wartosc fifo, jesli zostanie przekazana przez argument */
     else if(argc == 2) {
          fifo = argv[1];
     }
/* błąd, gdy zła ilość argumentów */
     else {
          perror("Zla ilosc argumentow");
          exit(EXIT_FAILURE);
     }
/* zarodek do randa */
     srand(time(NULL));

/* tworzymy plik potoku o nazwie przekazanej w argumencie fifo */
     if(mkfifo(fifo, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) == -1) {
          perror("Blad mkfifo");
          exit(EXIT_FAILURE);
     }
/* tworzymy proces potomny */
     switch(fork()) {
         case -1:
              perror("Blad przy tworzeniu procesu potomnego");
              exit(EXIT_FAILURE);
              break;
         case 0:
/* wywołanie programu konsument.x */
              execl("./konsument.x", "./konsument.x", fifo, NULL);
              perror("Blad execl konsument");
              exit(EXIT_FAILURE);
              break;
         default:
/* tworzymy proces potomny */
              switch(fork()) {
                   case -1:
                        perror("Blad przy tworzeniu procesu potomnego");
                        exit(EXIT_FAILURE);
                        break;
                   case 0:
/* wywołanie programu producent.x */
                        execl("./producent.x", "./producent.x", fifo, NULL);
                        perror("Blad execl");
                        exit(EXIT_FAILURE);
                        break;
                default:
/* proces macierzysty czeka na swoje dziecko */
                        wait(NULL);
                        break;
             }
/* proces macierzysty czeka na swoje dziecko */
             wait(NULL);
/* usunięcie dowiązania do pliku i jednoczesne usunięcie pliku, jeśli było to ostatnie dowiązanie */
             unlink(fifo);
/* wywołanie komendy w terminalu, która sprawdza, czy pliki są identyczne */
             system("diff -s magazyn.txt schowek.txt");
             break;
     }
     return 0;
}
