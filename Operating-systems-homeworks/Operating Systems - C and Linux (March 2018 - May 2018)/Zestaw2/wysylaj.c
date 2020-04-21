/*********************************************************
*                        Zadanie 2
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>     /* free */
#include <signal.h>     /* kill */
#include <sys/types.h>  /* kill, wait */
#include <sys/wait.h>   /* wait*/
#include <string.h>     /* strcpy */
#include <unistd.h>     /* execl */
#include <errno.h>      /* errno */
#include "procinfo.h"   /* procinfo */

int kill(pid_t pid, int sig);

int main(int argc, char *argv[]) {

/* na początku musimy sprawdzić czy użytkownik podał dobrą ilość argumentów */
    if(argc != 3) {
        perror("Zła liczba argumentów");
        printf("\nAby poprawnie uruchomic program wpisz w terminalu: \n\"%s rodzaj_akcji(d/i/p) nr_sygnalu\"\n", argv[0]);
        exit(0);
    }

    int i;
    pid_t p;
    char *argu[argc];

    for(i = 0; i < argc; i++) {
        argu[i] = malloc(sizeof(argv[i]));
    }

    for(i = 0; i < argc; i++) {
        strcpy(argu[i], argv[i]);
    }

    procinfo(argu[0]);

    switch(p = fork()) {
        case -1:
            perror("Blad przy tworzeniu procesu");
            exit(0);
            break;
        case 0:
            execl("./obsluga.x", "./obsluga.x", argu[1], argu[2], NULL);
            perror("Blad funkcji execl");
            exit(0);
            break;
        default:
            sleep(1);
            kill(p, 0);
            if(errno != ESRCH) {
                kill(p, atoi(argu[2]));
            }
            break;
    }
    wait(NULL);

    for(i = 0; i < argc; i++) {
        free(argu[i]);
    }

    printf("Zakonczenie procesu o PID = %d i PPID = %d\n", getpid(), getppid());

    return 0;
}
