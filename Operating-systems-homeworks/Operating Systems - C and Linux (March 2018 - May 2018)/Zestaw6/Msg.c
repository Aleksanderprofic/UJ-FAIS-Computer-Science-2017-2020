/*********************************************************
*                        Zadanie 1
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>        /* kolejki */
#include <sys/ipc.h>          /* kolejki */
#include <sys/msg.h>          /* kolejki */

#include "Msg.h"

/* Tworzy kolejkę komunikatów. Funkcja zwraca identyfikator kolejki komunikatów. */
int msgCreate(int id) {
     key_t key;
     int msqid;

     if((key = ftok(".", id)) == -1) {
          perror("msgCreate ftok");
          exit(EXIT_FAILURE);
     }
     if((msqid = msgget(key, IPC_CREAT | 0666)) == -1) {
          perror("msgCreate msgget");
          exit(EXIT_FAILURE);
     }

     return msqid;
}

/* Usuwa kolejkę komunikatów o identyfikatorze msqid. */
void msgRm(int msqid) {
     if(msgctl(msqid, IPC_RMID, NULL)) {
          perror("msgRm");
          exit(EXIT_FAILURE);
     }
     printf("Usuwam kolejke...\n");
}

/* Wysyła komunikat wskazywany przez msg do kolejki o identyfikatorze msqid. */
void msgSend(int msqid, komunikat *msg) {
     if(msgsnd(msqid, msg, sizeof(komunikat), 0) == -1) {
          perror("msgSend msgsnd");
          exit(EXIT_FAILURE);
     }
}

/* Odbiera z kolejki msqid komunikat typu mtype i zapisuje do msg. */
void msgRecv(int msqid, komunikat *msg, int mtype) {
     if(msgrcv(msqid, msg, sizeof(komunikat), mtype, 0) == -1) {
          perror("msgRecv msgrcv");
          exit(EXIT_FAILURE);
     }
}

/* Wypisuje informacje o kolejce komunikatów. */
void msgInfo(int msqid) {
     struct msqid_ds buf;
     if(msgctl(msqid, IPC_STAT, &buf) == -1) {
          perror("msgInfo msgctl");
          exit(EXIT_FAILURE);
     }
     printf("Current number of bytes in q: %lu\nCurrent number of messages in q: %lu\nPID of last msgsnd: %d\nPID of last msgrcv: %d\n", buf.msg_cbytes, buf.msg_qnum, buf.msg_lspid, buf.msg_lrpid);
}

/* Zwraca ilość komunikatów w kolejce. */
int Qnum(int msqid) {
     struct msqid_ds buf;
     if(msgctl(msqid, IPC_STAT, &buf) == -1) {
          perror("msgInfo msgctl");
          exit(EXIT_FAILURE);
     }
     return buf.msg_qnum;
}
