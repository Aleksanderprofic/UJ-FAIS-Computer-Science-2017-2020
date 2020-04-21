/*********************************************************
*                       Zadanie 1
*                   Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>         /* exit, rand */
#include <unistd.h>         /* fork, pipe, write, read, usleep */
#include <sys/types.h>        /* wait */
#include <sys/wait.h>         /* wait */
#include <time.h>             /* time */

#define SIZE 20

char buf[SIZE];

int usleep();

void producent(int pipe_fd[]) {
     FILE *fp;
/* zamknięcie desktryptora odczytu */
     close(pipe_fd[0]);
/* otwarcie pliku magazyn.txt */
     fp = fopen("./magazyn.txt", "r");
/* dopóki nie dojdziemy do końca pliku to pętla będzie się wykonywać */
     while(!feof(fp)) {
/* uśpienie programu na losową ilość sekund */
          usleep(rand()%5555555);
/* czytanie danych z pliku wskazywanego przez fp i zapisywanie do buf */
          if(fgets(buf, SIZE, fp) == buf) {
/* przesyłanie danych z buf przez potok pipe_fd */
          if(write(pipe_fd[1], &buf, SIZE) == -1) {
               perror("Blad write");
               exit(EXIT_FAILURE);
          }
          printf("Producent >>>>> %s\n", buf);
          }
     }
     /* zamknięcie deskryptora zapisu */     if(close(pipe_fd[1]) == -1) {
         perror("Blad close producent");
         exit(EXIT_FAILURE);
    }
/* zamknięcie pliku magazyn.txt */
     if(fclose(fp) == EOF) {
          perror("Blad fclose producent");
          exit(EXIT_FAILURE);
     }
}

void konsument(int pipe_fd[]) {
    FILE *fp;
    ssize_t ret_read;
/* zamknięcie deskryptora zapisu */
    close(pipe_fd[1]);
/* otwarcie pliku schowek.txt */
    fp = fopen("./schowek.txt", "w");
/* czytanie z deskryptora dopóki funkcja read zwraca niezerową, dodatnią ilość bajtów */
    while((ret_read = read(pipe_fd[0], &buf, SIZE)) > 0) {
/* uśpienie programu na losową ilość sekund */
         usleep(rand()%5555555);
/* zapisywanie danych z bufora do pliku schowek.txt */
         if(fputs(buf, fp) < 0) {
              perror("Blad fputs");
              exit(EXIT_FAILURE);
         }
         printf("Konsument <<< %s\n", buf);
    }
/* jeśli czytanie zakończy się niepowodzeniem */
    if(ret_read == -1) {
         perror("Blad read");
         exit(EXIT_FAILURE);
    }
/* zamknięcie deskryptora odczytu */
    if(close(pipe_fd[0]) == -1) {
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
     if(argc != 1) {
          perror("Zla ilosc argumentow");
          exit(EXIT_FAILURE);
     }
/* zarodek do randa */
     srand(time(NULL));

     int ret_pipe, pipe_fd[2];
/* tworzenie deskryptorów odczytu i zapisu */
     ret_pipe = pipe(pipe_fd);

/* błąd tworzenia potoku */
     if(ret_pipe == -1) {
          perror("Pipe");
          exit(EXIT_FAILURE);
     }

/* tworzenie procesu potomnego */
     switch(fork()) {
          case -1:
               perror("Blad przy tworzeniu procesu potomnego");
               exit(EXIT_FAILURE);
               break;
          case 0:
/* wywołanie funkcji konsument() */
               konsument(pipe_fd);
               break;
          default:
/* wywołanie funkcji producent() */
               producent(pipe_fd);
/* proces czeka na swoje dziecko */
               wait(NULL);
/* tworzenie procesu potomnego */
               switch(fork()) {
                    case -1:
                         perror("Blad przy tworzeniu procesu potomnego");
                         exit(EXIT_FAILURE);
                         break;
                    case 0:
/* sleep, żeby to troszkę ładniej wyglądało */
                         sleep(1);
/* wywołanie przez execl komendy diff w terminalu i obsługa błędów w przypadku niepowodzenia */
                         execl("/bin/sh", "sh", "-c", "diff -s magazyn.txt schowek.txt", NULL);
                         perror("Blad execl");
                         exit(EXIT_FAILURE);
                         break;
                    default:
/* proces czeka na swoje dziecko */
                    wait(NULL);
                    break;
               }
               break;
          }
     return 0;
}
