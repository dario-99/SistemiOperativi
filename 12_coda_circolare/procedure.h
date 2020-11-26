#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define NUM_PROD 5
#define NUM_CONS 5

#define SIZE 3

#define SPAZIO_DISP 0
#define MSG_DISP 1
#define MUTEX_C 2
#define MUTEX_P 3


typedef struct {
    int buff[SIZE];
    int coda;
    int testa;
}coda;

void init_struct(coda* c);
void produci(int ds_sem, coda* c);
void consuma(int ds_sem, coda* c);

#endif