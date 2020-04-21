/*********************************************************
*                    Aleksander Profic
*********************************************************/

#include <stdio.h>            /* perror, printf */
#include <sys/types.h>        /* shmget, shmctl */
#include <sys/ipc.h>          /* shmget, shmctl */
#include <sys/shm.h>          /* shmget, shmctl */
#include <stdlib.h>           /* exit */

/* Funkcja tworzy pamięć dzieloną o rozmiarze size. Zwraca identyfikator pamięci dzielonej shmid. */
int shmCreate(int id, int size) {
     key_t key;
     int shmid;

     if((key = ftok(".", id)) == -1) {
          perror("shmCreate ftok");
          exit(EXIT_FAILURE);
     }
     if((shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
          perror("shmCreate shmget");
          exit(EXIT_FAILURE);
     }

     return shmid;
}

/* Funkcja uzyskuje dostęp do pamięci dzielonej i zwraca identyfikator pamięci dzielonej. */ 
int shmOpen(int id) {
     key_t key;
     int shmid;

     if((key = ftok(".", id)) == -1) {
          perror("shmOpen ftok");
          exit(EXIT_FAILURE);
     }
     if((shmid = shmget(key, 0, 0666)) == -1) {
          perror("shmOpen shmget");
          exit(EXIT_FAILURE);
     }

     return shmid;
}

/* Usuwa dany segment pamięci dzielonej shmid. */ 
void shmRm(int shmid) {

     if(shmctl(shmid, IPC_RMID, (struct shmid_ds *)0) == -1) {
          perror("shmRm");
          exit(EXIT_FAILURE);
     }
}

/* Dowiązuje segment pamięci dzielonej shmid. Zwraca adres odwzorowania. */
void* shmAt(int shmid) {
     void * adres;
     
     if((adres = shmat(shmid, NULL, 0)) == (void *)-1) {    /* spytać o takie castowanie */
          perror("shmAt shmat");
          exit(EXIT_FAILURE);
     }

     return adres;
}

/* Usuwa dowiązanie do segmentu pamięci dzielonej dowiązanej pod adres. */
void shmDt(void *adres) {

     if(shmdt(adres) == -1) {
          perror("shmDt");
          exit(EXIT_FAILURE);
     }
}