/*********************************************************
*                    Aleksander Profic
*********************************************************/

#ifndef SHMEM_H
#define SHMEM_H

/* Funkcja tworzy pamięć dzieloną o rozmiarze size. Zwraca identyfikator pamięci dzielonej shmid. */
int shmCreate(int id, int size);

/* Funkcja uzyskuje dostęp do pamięci dzielonej i zwraca identyfikator pamięci dzielonej. */ 
int shmOpen(int id);

/* Usuwa dany segment pamięci dzielonej shmid. */ 
void shmRm(int shmid);

/* Dowiązuje segment pamięci dzielonej shmid. Zwraca adres odwzorowania. */
void* shmAt(int shmid);

/* Usuwa dowiązanie do segmentu pamięci dzielonej dowiązanej pod adres. */
void shmDt(void *adres);

#endif //SHMEM_H