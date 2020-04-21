/*********************************************************
*                Zadanie - Algorytm piekarni
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>      /* exit */
#include <unistd.h>      /* fork */
#include <sys/wait.h>    /* wait */
#include <semaphore.h>

#include "shmem.h"

/* liczba utworzonych procesow */
#define P_NR 5

/*
Przesuniecie kursora do pozycji x, y na ekranie konsoli: \033[x;yH
Włącz normalny tekst:  \033[0m
Włącz pogrubienie tekstu:  \033[1m
Włącz podkreślenie tekstu:  \033[4m
Włącz migający tekstu:  \033[5m
Włącz inwersje tekstu:  \033[7m
Zmiana koloru tekstu: \033[xm
Zamiast symbolu x należy wstawić liczbę między 30 a 49.
Wyczyszczenie ekranu: \033c
*/

/* struktura pamięci dzielonej */
typedef struct shared {
     volatile int counter;
     volatile int num[P_NR];
     volatile int choosing[P_NR];
} sharedMem;

/* funkcja do obsługi sygnałow */
void signal_handler(int nr_syg) {
     int shmid = shmOpen('B');
     printf("Sygnal %d zostal obsluzony przez proces o id: %d\n", nr_syg, getpid());
     shmRm(shmid);
     exit(EXIT_SUCCESS);
}

int main() {

     /* wyczyszczenie ekranu */
     system("clear");

     /* przygotowanie funkcji na przyjecie sygnału */
     if(signal(2, signal_handler) == SIG_ERR) {
          printf("Funkcja signal ma problem z sygnalem SIGINT");
     }

     /* tworzenie zmiennych */
     sharedMem *shm;
     int i, shmid;
     char temp[P_NR];

     /* tworzenie pamięci dzielonej */
     shmid = shmCreate('B', sizeof(sharedMem));

     /* tworzenie dowiązania do pamięci dzielonej */
     shm = (sharedMem *)shmAt(shmid);
     shm->counter = 0;

     /* inicjalizacja tablic z pamięci dzielonej na wartości 0 */
     for(i = 0; i < P_NR; i++) {
          shm->num[i] = 0;
          shm->choosing[i] = 0;
     }

     /* tworzenie procesow */
     for(i = 0; i < P_NR; i++) {
          /* przyporządkowanie cyfr do tablicy znakowej */
          temp[i] = i+48;
          switch(fork()) {
               case -1:
                    perror("fork");
                    exit(EXIT_FAILURE);
                    break;
               case 0:
                    execl("./process.x", "./process.x", &temp[i], NULL);
                    perror("fork execl");
                    exit(EXIT_FAILURE);
                    break;
               default:
                    break;
          }
     }
     
     /* usunięcie dowiązania pamięci dzielonej */
     shmDt(shm);

     /* proces main.x czeka na procesy process.x */
     for(i = 0; i < P_NR; i++) {
          wait(NULL);
     }
     

     return 0;
}