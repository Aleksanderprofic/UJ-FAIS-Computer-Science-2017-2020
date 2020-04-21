/*********************************************************
*                        Zadanie 1.
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>      /* funkcja perror, printf */
#include <stdlib.h>     /* funkcja exit */
#include <unistd.h>     /* funkcja close, read, write */
#include <sys/types.h>  /* funkcja open */
#include <fcntl.h>      /* funkcja open */
#include <sys/stat.h>   /* funkcja open */
#include <errno.h>      /* funkcja errno */

#define MAX 256

int main(int argc, char * argv[]) {

/* na początku musimy sprawdzić czy użytkownik podał dobrą ilość argumentów */
    if(argc != 3) {
        perror("Podana ilosc argumentow jest bledna");
        printf("\nAby prawidlowo uruchomic program w terminalu, wpisz komende: \n\"%s nazwa_pliku_kopiowanego nazwa_pliku_docelowego\"\n", argv[0]);
        exit(0);
    }

/* tworzymy zmienne, potrzebne w tym zadaniu, np. do przechowywania deskryptora pliku */
    int fdDocelowy, fdKopiowany;
    char buf[MAX];
    ssize_t ret_read, ret_write;

/* sprawdzamy czy pliki otworzyły się poprawnie */
    if((fdKopiowany = open(argv[1], O_RDONLY)) == -1) {
        perror("Blad przy otwieraniu pliku do odczytu");
        exit(0);
    }
/* dodane 2 flagi O_CREAT w przypadku, gdy plik nie istnieje to jest tworzony
*  oraz O_TRUNC, która czyści i zeruje plik */
    if((fdDocelowy = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1) {
        perror("Blad przy otwieraniu lub tworzeniu pliku do zapisu");
        exit(0);
    }

/* czytanie i zapisywanie plików wraz z obsługą błędów */

    /* dopóki funkcja read zwraca ilość bajtów większą od 0, to wykonujemy operacje czytania
    jeśli zwróci 0, to przestajemy odczytywać i program wykonuje kolejne polecenia,
    a jeśli zwróci -1 to oznacza błąd, pętla się przerywa i zostaje on obsłużony */
    while((ret_read = read(fdKopiowany, &buf, MAX)) > 0) {
        ret_write = write(fdDocelowy, &buf, ret_read);      /* zapisujemy do pliku tyle bajtów ile zostało odczytanych funkcją read */
        if(ret_write != ret_read) {                         /* jeśli ilość bajtów odczytanych i zapisanych się różni */
            perror("Blad zapisu pliku");                    /* to oznacza błąd zapisu pliku i program zostaje zakończony */
            exit(0);
        }
    }
    if(ret_read == -1) {                                    /* gdy funkcja read zwraca -1 oznacza, że wystąpił błąd odczytu pliku */
        perror("Blad odczytu pliku");                       /* i program zostaje zakończony */
        exit(0);
    }

/* zamykanie plików wraz z obsługą błędów */
    if(close(fdKopiowany) == -1) {
        perror("Blad zamkniecia pliku kopiowanego");
        exit(0);
    }
    if(close(fdDocelowy) == -1) {
        perror("Blad zamkniecia pliku docelowego");
        exit(0);
    }

    return 0;
}
