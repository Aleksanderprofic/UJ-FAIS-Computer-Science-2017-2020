/*********************************************************
*                        Zadanie 2
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>      /* exit */
#include "shmem.h"

int main(int argc, char * argv[]) {
     
/* sprawdza ilość argumentow */
     if(argc == 1) {
          /* wypisuje informacje o prawidlowym uzyciu programu */
          print();
          exit(EXIT_SUCCESS);
     }
     /* deklaracja zmiennych potrzebnych w dalszej czesci programu */
     int shmid, size, i = 0, cnt = 0;

     if(argc == 3) {
          if(argv[1][0] == 'c') {
               /* Tworzy segment pamięci dzielonej o rozmiarze size bajtów. */
               size = atoi(argv[2]);
               shmCreate('A', size); 
               exit(EXIT_SUCCESS);
          }
          else {
               perror("Argument 2");
               /* wypisuje informacje o prawidlowym uzyciu programu */
               print();
               exit(EXIT_FAILURE);
          }
     }
     
     if(argc == 2) {
          switch(argv[1][0]) {
          /* Tworzy segment pamięci dzielonej o domyślnym rozmiarze 256 bajtów. */
          case 'c':
               size = 256;
               shmCreate('A', size);
               break;
          /* Usuwa segment pamięci dzielonej */
          case 'd':
               shmid = shmOpen('A');
               shmRm(shmid);
               break;
          /* Wypisuje zawartość pamięci dzielonej na standardowe wyjście. */
          case 'r':
               shmid = shmOpen('A');
               char * wskaznik1 = (char *)shmAt(shmid);
               printf("%s\n", wskaznik1);

               shmDt(wskaznik1);
               break;
          /* Wypisuje informacje o pamięci dzielonej. */
          case 'i':
               shmid = shmOpen('A');
               shmInfo(shmid);
               break;
          case 'w':
          /* Kopiuje zawartość standardowego wejścia do pamięci dzielonej. Sprawdza rozmiar segmentu. */
               shmid = shmOpen('A');
               char * wskaznik2;
               wskaznik2 = (char *)shmAt(shmid);

               size = shmSize(shmid);

               printf("Rozmiar segmentu: %d\n", size);
               
               do {
                    fscanf(stdin, "%c", &wskaznik2[i]);
                    cnt++;
                    printf("zapisałem %c na pozycji %d\n", wskaznik2[i], i);

               } while (wskaznik2[i++] != '\0' && cnt < size);

               shmDt(wskaznik2);
               break;
          /* wypisuje informacje o prawidlowym uzyciu programu */
          default:
               perror("Argument 1");
               print();
               exit(EXIT_FAILURE);
               break;
          }
     }

     return 0;
}