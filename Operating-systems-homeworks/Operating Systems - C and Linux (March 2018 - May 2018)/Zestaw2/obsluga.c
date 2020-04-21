/*********************************************************
*                        Zadanie 1
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>         /* atoi */
#include <string.h>         /* strlen */
#include <signal.h>         /* sygnaly */
#include <sys/types.h>      /* procinfo */
#include <unistd.h>         /* procinfo */
#include "procinfo.h"       /* procinfo */

//typedef void (*sighandler_t)(int);
//sighandler_t signal(int signum, sighandler_t handler);

void signal_handler(int nr_syg) {
    printf("Sygnal %d zostal obsluzony przez proces o id: %d\n", nr_syg, getpid());
}

int main(int argc, char* argv[]) {
    printf("Uruchomiony program obsluga.x...\n");
    if(argc != 3) {
        perror("Zla ilosc argumentow");
        printf("Aby poprawnie uruchomic program wpisz w terminalu: \n\"%s rodzaj_akcji(d/i/p) nr_sygnalu\"\n", argv[0]);
        exit(0);
    }
    if(strlen(argv[1]) != 1) {
        perror("Niepoprawny argument 1");
        exit(0);
    }

    int nr_sygnalu;
    nr_sygnalu = atoi(argv[2]);

    procinfo(argv[0]);

    switch(argv[1][0]) {
        case 'd':
            printf("Obsluga wybranego sygnalu w trybie domyślnym\n");
            if(signal(nr_sygnalu, SIG_DFL) == SIG_ERR) {
                printf("Funkcja signal ma problem z sygnalem %d", nr_sygnalu);
            }
            break;
        case 'i':
            printf("Ignorowanie sygnalu\n");
            if(signal(nr_sygnalu, SIG_IGN) == SIG_ERR) {
                printf("Funkcja signal ma problem z sygnalem %d", nr_sygnalu);
            }
            break;
        case 'p':
            printf("Obsluga wybranego sygnalu\n");
            if(signal(nr_sygnalu, signal_handler) == SIG_ERR) {
                printf("Funkcja signal ma problem z sygnalem %d", nr_sygnalu);
            }
            break;
        default:
            printf("Bledny rodzaj akcji!!\n");
            return 0;
    }
    pause();

    printf("Zakonczenie procesu o PID = %d i PPID = %d\n", getpid(), getppid());

    return 0;
}
