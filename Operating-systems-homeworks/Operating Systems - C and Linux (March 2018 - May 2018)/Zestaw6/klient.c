/*********************************************************
*                        Zadanie 2
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>           /* exit */
#include <unistd.h>           /* getpid */
#include <ctype.h>            /* toupper */

#include "Msg.h"

int main(int argc, char * argv[]) {

     /* sprawdzenie ilości argumentow */
     if(argc != 1) {
          perror("Ilosc argumentow programu");
          exit(EXIT_FAILURE);
     }

     /* tworzenie zmiennych i przypisanie id kolejki */
     komunikat message;
     int msqid = msgCreate('A');

     printf("The message id is: %d\n", msqid);

     /* uzytkownik podaje komunikat z klawiatury */
     printf("Prosze podac %d literowy komunikat do wyslania: ", SIZE-1);
     fgets(message.mtext, SIZE, stdin);

     /* ustawienie pidu komunikatu na pid klienta, zeby serwer wiedzial gdzie odeslac wiadomosc */
     message.pid = getpid();
     /* ustawienie typu wiadomosci na 10, poniewaz serwer odbiera wiadomosci o typie 10 */
     message.mtype = 1;

     /* wyslanie komunikatu do serwera */
     printf("\nCLIENT %ld ----> Sending message to the SERVER -> %s\n", message.pid, message.mtext);
     msgSend(msqid, &message);

     msgInfo(msqid);

     /* odebranie komunikatu z serwera */
     msgRecv(msqid, &message, message.pid);
 
     printf("\nCLIENT %ld ----> Message recevied from SERVER: %s\n", message.pid, message.mtext);

     msgInfo(msqid);

     return 0;
}