#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define NUM_THREAD 100
#define ELEM 1000
#include <pthread.h>

typedef struct{
    int prodScalare;
    pthread_mutex_t m;
    int v1[NUM_THREAD * ELEM];
    int v2[NUM_THREAD * ELEM];
}buf;

typedef struct{
    buf* b;
    int start;
    int end;
}prod_s;

void initBuf(buf* b);
/*
    Funzione che calcola il prodotto scalare tra due vettori, dato start ed end
    che indicano dove iniziare e dove finire di calcolare il prodotto
*/
int prodottoScalare(int *v1, int *v2, int start, int end);
/*
    funzione eseguita dal thread, ricevera' in input i vettori e inzio e fine
*/
void* t_prodScalare(void*);

#endif