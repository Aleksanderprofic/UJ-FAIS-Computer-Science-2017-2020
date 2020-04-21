/*********************************************************
*                        Zadanie 2
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>           /* exit */
#include <ctype.h>            /* toupper */
#include <unistd.h>           /* sleep */

#include "Msg.h"

int main(int argc, char * argv[]) {
     /* sprawdzenie ilości argumentow */
     if(argc != 1) {
          perror("Ilosc argumentow programu");
          exit(EXIT_FAILURE);
     }

     /* tworzenie zmiennych */
     int i;
     char temp;
     char tmp[100];
     komunikat message;

     /* tworzenie kolejki komunikatow */
     int msqid = msgCreate('A');

     printf("The message id is: %d\n", msqid);
     msgInfo(msqid);
     
     /* głowna pętla serwera, ktory najpierw odbiera, a potem wysyła komunikaty */
     while(1) {
          /* odebranie komunikatu od klientow */
          msgRecv(msqid, &message, 1);

          i = 0;

          /* zmiana liter komunikatu na duze */
          printf("SERVER ----> Message recevied from CLIENT with PID: %ld: %s\n", message.pid, message.mtext);
          while(message.mtext[i] != '\0') {
               temp = toupper(message.mtext[i]);
               message.mtext[i++] = temp;
          }
          printf("SERVER ----> Sending the message to the CLIENT with PID: %ld: %s\n", message.pid, message.mtext);

          /* zmiana typu komunikatu na pid klienta ktory przyslal wiadomosc */
          message.mtype = message.pid;

          /* wysłanie wiadomości zwrotnej do klienta */
          msgSend(msqid, &message);

          /* sleep, zeby wszystko ladniej wygladalo */
          sleep(3);

          /* warunek pytający o to czy kontynuować pętle, jezeli ilosc komunikatow w kolejce jest rowna 0 */
          if(Qnum(msqid) == 0) {
               printf("Queue is empty. Do u want to wait for another message?\n");
               
               do {
                    printf("\nPress n for NO or any other character for YES.\n");
                    scanf(" %s", tmp);
               } while(tmp[1] != '\0');

               /* jezeli uzytkownik podal n z klawiatury to kolejka jest usuwana i pętla przerywana */
               if(tmp[0] == 'n') {
                    msgRm(msqid);
                    break;
               }
          }
     }

     return 0;
}    