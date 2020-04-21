/*********************************************************
*                        Zadanie 1
*                    Aleksander Profic
*********************************************************/

#ifndef MSG_H
#define MSG_H

#define SIZE 21

typedef struct komunikat_t {
     long mtype;              /* typ komunikatu   */
     long pid;                /* pid procesu */
     char mtext[SIZE];        /* tekst komunikatu */
} komunikat;

/* Tworzy kolejkę komunikatów. Funkcja zwraca identyfikator kolejki komunikatów. */
int msgCreate(int id); 

/* Usuwa kolejkę komunikatów o identyfikatorze msgid. */
void msgRm(int msqid);

/* Wysyła komunikat wskazywany przez msg do kolejki o identyfikatorze msgid. */
void msgSend(int msqid, komunikat *msg);

/* Odbiera z kolejki msgid komunikat typu mtype i zapisuje do msg. */
void msgRecv(int msqid, komunikat *msg, int mtype);

/* Wypisuje informacje o kolejce komunikatów. */
void msgInfo(int msqid);

/* Zwraca ilość komunikatów w kolejce. */
int Qnum(int msqid);

#endif