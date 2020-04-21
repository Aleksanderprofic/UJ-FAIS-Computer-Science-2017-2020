/*********************************************************
*                       Zadanie 5.2
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>      /* funkcja perror, printf */
#include <stdlib.h>     /* funkcja exit */
#include <unistd.h>     /* funkcja fork, procinfo */
#include <sys/types.h>  /* funkcja procinfo, wait */
#include <string.h>     /* funkcja strcpy */
#include <sys/wait.h>   /* funkcja wait */
#include "procinfo.h"   /* funkcja procinfo z zadania 3 */

int main(int argc, char *argv[]) {

/* na początku musimy sprawdzić czy użytkownik podał dobrą ilość argumentów */
    if(argc != 1) {
        perror("Zła liczba argumentów");
        printf("\nAby prawidlowo uruchomic program w terminalu, wpisz komende: \n\"%s\"\n", argv[0]);
        exit(EXIT_FAILURE);
    }

/* tworzymy iterator wykorzystywany w pętli z forkiem */
    int i, child_cnt = 0;

/* wypisanie informacji o procesie */
    procinfo(argv[0]);

    for(i = 0; i < 3; i++) {
        switch(fork()) {
            case -1:
                perror("Blad przy tworzeniu procesu");
                exit(0);
                break;
            case 0: /* proces potomny */
                strcpy(argv[0], "child");
                procinfo(argv[0]);
                break;
            default: /* proces macierzysty */
                child_cnt++;
                strcpy(argv[0],"parent");
                break;
        }
        if(child_cnt == 1) {
            //wait(NULL); można było dać wait tutaj zamiast tego poza pętlą
            break;
        }
    }

    if(child_cnt == 1) {
        wait(NULL);
    }

    return 0;
}
