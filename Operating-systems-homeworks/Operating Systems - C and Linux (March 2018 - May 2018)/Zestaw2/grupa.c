/*********************************************************
*                        Zadanie 3
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>         /* atoi */
#include <string.h>         /* strlen */
#include <signal.h>         /* kill */
#include <sys/types.h>      /* kill, wait */
#include <sys/wait.h>       /* wait */
#include <string.h>         /* strcpy */
#include <unistd.h>         /* fork */
#include <errno.h>          /* errno */
#include "procinfo.h"       /* procinfo */

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

int kill(pid_t pid, int sig);

void signal_handler(int nr_syg) {
    printf("Sygnal %d zostal obsluzony!\n", nr_syg);
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        perror("Zla ilosc argumentow");
        printf("Aby poprawnie uruchomic program wpisz w terminalu: \n\"%s rodzaj_akcji(d/p) nr_sygnalu\"\n", argv[0]);
        exit(0);
    }

    int i, child_cnt = 0, nr_sygnalu;
    nr_sygnalu = atoi(argv[2]);

    procinfo(argv[0]);

    for(i = 0; i < 5; i++) {
        switch(fork()) {
            case -1:
                perror("Blad przy tworzeniu procesu");
                exit(0);
                break;
            case 0:
                child_cnt = 0;
                switch(argv[1][0]) {
                    case 'd':
                        printf("Obsluga wybranego sygnalu w trybie domyślnym\n");
                        if(signal(nr_sygnalu, SIG_DFL) == SIG_ERR) {
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
                sleep(4);
                break;
            default:
                child_cnt++;
                break;
        }
        if(child_cnt == 0) break;
    }

    if(child_cnt != 0) {
        signal(nr_sygnalu, SIG_IGN);
        sleep(2);
        if(errno != ESRCH) {
            kill(0, nr_sygnalu);
        }
    }

    for(i = 0; i < child_cnt; i++) {
        wait(NULL);
    }
    printf("Zakonczenie procesu o PID = %d i PPID = %d\n", getpid(), getppid());
    return 0;
}
