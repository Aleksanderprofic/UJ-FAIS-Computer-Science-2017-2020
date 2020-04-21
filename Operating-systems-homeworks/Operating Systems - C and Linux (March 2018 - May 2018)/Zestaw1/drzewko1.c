/*********************************************************
*                       Zadanie 5.1
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
        exit(0);
    }

/* tworzymy iterator wykorzystywany w pętli z forkiem */
    int i, child_cnt = 0, p;

/* wypisanie informacji o procesie */
    procinfo(argv[0]);

    for(i = 0; i < 3; i++) {
        switch(p = fork()) {
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
        if(p == 0) break;
    }

/* wywołuje funkcje wait tyle razy, ile proces macierzysty miał dzieci */
    for(i = 0; i < child_cnt; i++) {
        wait(NULL);
    }

    return 0;
}
