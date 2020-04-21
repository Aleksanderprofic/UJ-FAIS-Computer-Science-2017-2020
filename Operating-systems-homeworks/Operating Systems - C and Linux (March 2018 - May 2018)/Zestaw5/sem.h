/*********************************************************
*                    Zadanie 1 zestaw 4
*                    Aleksander Profic
*********************************************************/

#ifndef SEM_H
#define SEM_H

int semDecl(int id, int nSem);
void semInit(int semid, int nSem, int val);
void semRm(int semid, int nSem);
void semP(int semid, int nSem);
void semV(int semid, int nSem);
void semZ(int semid);
void semInfo(int semid);
void semInfo2(int semid);

#endif // SEM_H