/*********************************************************
*                        Zadanie 6
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>      /* funkcja perror, printf */
#include <stdlib.h>
#include <sys/types.h>  /* procinfo */
#include <unistd.h>     /* procinfo */
#include "procinfo.h"

int main(int argc, char* argv[]) {

    if(argc != 2) {
        perror("Zla liczba argumentow");
        exit(0);
    }
    procinfo(argv[1]);
    return 0;
}
