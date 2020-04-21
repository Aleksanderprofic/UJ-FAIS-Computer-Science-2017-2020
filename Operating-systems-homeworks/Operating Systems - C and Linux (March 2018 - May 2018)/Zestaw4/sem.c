/*********************************************************
*                        Zadanie 1
*                    Aleksander Profic
*********************************************************/

#include <sys/sem.h>          /* semget */
#include <stdio.h>            /* perror */
#include <stdlib.h>           /* exit */

#ifdef _SEM_SEMUN_UNDEFINED
     union semun {
       int val;               /* wartosc dla SETVAL */
       struct semid_ds *buf;  /* bufor dla IPC_STAT, IPC_SET */
       unsigned short *array; /* tablica dla GETALL, SETALL */
       struct seminfo *__buf; /* bufor dla IPC_INFO (specyfika Linuksa) */
};
#endif

union semun arg;
struct sembuf buf;

/* Uzyskuje dostęp lub tworzy jeden semafor. Zwraca identyfikator semafora semid. */
int semDecl(int id) {
     key_t key;
     int semid;

     printf("Uzyskanie dostepu/tworzenie semafora\n");

     if((key = ftok(".", id)) == -1) {
          perror("ftok");
          exit(EXIT_FAILURE);
     }
     if((semid = semget(key, 1, IPC_CREAT | 0666)) == -1) {
          perror("semget");
          exit(EXIT_FAILURE);
     }

     return semid;
}
/* inicjalizuje semafor wartoscia val */
void semInit(int semid, int val) {
     arg.val = val;
     if((semctl(semid, 0, SETVAL, arg)) == -1) {
          perror("semctl semInit");
          exit(EXIT_FAILURE);
     }
}
/* usuwa semafor */
void semRm(int semid) {
     if((semctl(semid, 1, IPC_RMID, arg)) == -1) {
          perror("semctl semRm");
          exit(EXIT_FAILURE);
     }
}
/* opuszcza semafor: zmniejsza wartosc semafora o 1 lub czeka */
void semP(int semid) {
     buf.sem_num = 0;
     buf.sem_op = -1;
     buf.sem_flg = 0;
     if((semop(semid, &buf, 1)) == -1) {
          perror("semop semP");
          exit(EXIT_FAILURE);
     }
}
/* podnosi semafor: zwieksza wartosc semafora o 1 lub wznawia czekajacy proces */
void semV(int semid) {
     buf.sem_num = 0;
     buf.sem_op = 1;
     buf.sem_flg = 0;
     if((semop(semid, &buf, 1)) == -1) {
          perror("semop semV");
          exit(EXIT_FAILURE);
     }
}
/* funkcja czeka na wyzerowanie semafora */
void semZ(int semid) {
     buf.sem_num = 0;
     buf.sem_op = 0;
     buf.sem_flg = 0;
     if((semop(semid, &buf, 1)) == -1) {
          perror("semop semZ");
          exit(EXIT_FAILURE);
     }
}
/* funkcja wypisuje informacje o semaforze: wartosc, liczbe procesow czekajacych na opuszczenie/podniesienie */
void semInfo(int semid) {
     int semVal, nSemO, nSemP;
     semVal = semctl(semid, 0, GETVAL, arg);
     nSemP = semctl(semid, 0, GETNCNT, arg);
     nSemO = semctl(semid, 0, GETZCNT, arg);

     if((semVal == -1 || nSemP == -1 || nSemO == -1)) {
          perror("semctl semInfo");
          exit(EXIT_FAILURE);
     }

     printf("\nWartosc semafora: %d | Liczba proc czekajacych na opuszczenie: %d | Liczba proc czekajacych na podniesienie: %d\n", semVal, nSemO, nSemP);
}

void semInfo2(int semid) {
     int semVal, nSemP;
     semVal = semctl(semid, 0, GETVAL, arg);
     nSemP = semctl(semid, 0, GETNCNT, arg);

     if((semVal == -1 || nSemP == -1)) {
          perror("semctl semInfo2");
          exit(EXIT_FAILURE);
     }

     printf("\nWartosc semafora: %d | Liczba proc czekajacych na podniesienie: %d\n", semVal, nSemP);
}