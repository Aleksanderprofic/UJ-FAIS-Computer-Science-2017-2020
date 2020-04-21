/*********************************************************
*                        Zadanie 6
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>     /* funkcja exit */
#include <unistd.h>     /* funkcja fork, procinfo */
#include <sys/types.h>  /* funkcja procinfo */
#include <string.h>     /* funkcja strcpy */
#include "procinfo.h"   /* funkcja procinfo z zadania 3 */

int main(int argc, char *argv[]) {

/* na początku musimy sprawdzić czy użytkownik podał dobrą ilość argumentów */
    if(argc != 2) {
        perror("Zła liczba argumentów");
        printf("\nAby prawidlowo uruchomic program w terminalu, wpisz: \n\"%s sciezka_pliku_do_uruchomienia\"\n", argv[0]);
        exit(0);
    }
/* tworzymy iterator (wykorzystywany w pętli z forkiem) oraz pomocniczą tablice */
    int i;
    char *argu[argc];

/* przypisanie pamięci nowej tablicy */
    for(i = 0; i < argc; i++) {
        argu[i] = malloc(sizeof(argv[i]));
    }

/* kopiowanie argumentów funkcji main do nowej tablicy */
    for(i = 0; i < argc; i++) {
        strcpy(argu[i],argv[i]);
    }


/* wypisanie informacji o procesie */
    procinfo(argv[0]);

    for(i = 0; i < 3; i++) {
        switch(fork()) {
            case -1:
                perror("Blad przy tworzeniu procesu");
                exit(0);
                break;
            case 0: /* proces potomny */
                sleep(4);
                execv(argu[1], argu);
                perror("Blad funkcji execv");
                exit(0);
                break;
            default: /* proces macierzysty */
                strcpy(argv[0],"parent");
                sleep(1);
                break;
        }
        sleep(1);
    }
    sleep(4);
    procinfo(argv[0]);

/* zwolnienie pamięci przypisanej do pomocniczej tablicy */
    for(i = argc-1; i >= 0; i--) {
        free(argu[i]);
    }



    return 0;
}
