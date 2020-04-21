/*********************************************************
*                        Zadanie 1
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

/* Zwraca rozmiar pamięci dzielonej shmid. */
int shmSize(int shmid);

/* Wypisuje informacje o pamięci dzielonej: prawa dostępu, rozmiar, pid twórcy, liczbę dowiązań. */
void shmInfo(int shmid);

/* wypisuje informacje o prawidlowym uzyciu programu */
void print();

#endif //SHMEM_H