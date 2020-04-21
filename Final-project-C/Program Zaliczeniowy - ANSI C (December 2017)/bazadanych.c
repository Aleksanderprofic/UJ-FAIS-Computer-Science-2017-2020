/****************************************************
*       Program na zaliczenie z Jezyka C            *
*                                                   *
* 	 Baza danych studentów - Aleksander Profic      *
*                                                   *
*****************************************************/

#include "funkcje.h"

int main() {
    Student *l = NULL;
    FILE *fPointer;

    printf(LP"\x1b[4m\nBAZA DANYCH STUDENTOW I ROKU INFORMATYKI UJ FAIS!\n\x1b[24m"RESET);

    fPointer = fopen("save.txt", "r");
    /* czytanie z pliku, jesli istnieje */
    if (fPointer) {
        if(isalnum(fgetc(fPointer))) {
            rewind(fPointer);
            l = load(fPointer, l);
            printf("\x1b[3m\nLista studentow zostala wczytana z pliku save.txt\n\x1b[23m");
            fclose(fPointer);
        }
    }
    /* tworzenie pliku tekstowego, gdy jeszcze nie jest utworzony */
    else {
        fPointer = fopen("save.txt", "w");
        fclose(fPointer);
    }
    choice(l);

    return 0;
}
