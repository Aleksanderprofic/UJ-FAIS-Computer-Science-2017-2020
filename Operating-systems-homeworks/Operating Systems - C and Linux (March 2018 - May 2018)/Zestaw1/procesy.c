/*********************************************************
*                        Zadanie 4
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>      /* funkcja perror, printf */
#include <stdlib.h>     /* funkcja exit */
#include <unistd.h>     /* funkcja fork, procinfo */
#include <sys/types.h>  /* funkcja procinfo */
#include <string.h>     /* funkcja strcpy */
#include "procinfo.h"   /* funkcja procinfo z zadania 3 */

int main(int argc, char *argv[]) {

/* na początku musimy sprawdzić czy użytkownik podał dobrą ilość argumentów */
    if(argc != 1) {
        perror("Zła liczba argumentów");
        printf("\nAby prawidlowo uruchomic program w terminalu, wpisz: \n\"%s\"\n", argv[0]);
        exit(0);
    }
/* tworzymy iterator (wykorzystywany w pętli z forkiem) */
    int i;

/* zmiana nazwy procesu macierzystgo na "parent" i wypisanie informacji o procesie */
    strcpy(argv[0],"parent");
    procinfo(argv[0]);

    for(i = 0; i < 3; i++) {
        switch(fork()) {
            case -1:
                perror("Blad przy tworzeniu procesu");
                exit(0);
                break;
            case 0: /* proces potomny */
                strcpy(argv[0], "child");
                sleep(4);
                procinfo(argv[0]);
                break;
            default: /* proces macierzysty */
                strcpy(argv[0],"parent");
                sleep(1);
                break;
        }
        sleep(1);
    }

    sleep(13);
    procinfo(argv[0]);
    return 0;
}
