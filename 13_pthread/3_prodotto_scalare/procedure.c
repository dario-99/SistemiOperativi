#include "procedure.h"
#include <stdlib.h>
#include <stdio.h>


void initBuf(buf* b){
    pthread_mutex_init(&(b->m), NULL);
    b->prodScalare = 0;
    //init vettori con valori random, suppongo che sia stata chiamata srand
    for(int i=0; i<NUM_THREAD * ELEM; i++){
        b->v1[i] = rand()%10;
        b->v2[i] = rand()%10;
    }
}
/*
    Funzione che calcola il prodotto scalare tra due vettori, dato start ed end
    che indicano dove iniziare e dove finire di calcolare il prodotto
*/
int prodottoScalare(int *v1, int *v2, int start, int end){
    int sum = 0;
    int i;
    for(i=start;i<=end; i++){
        sum += v1[i] + v2[i];
    }
    return sum;
}
/*
    funzione eseguita dal thread, ricevera' in input i vettori e inzio e fine
*/
void* t_prodScalare(void* arg){
    prod_s* p = (prod_s*)arg;
    int sum = prodottoScalare(p->b->v1, p->b->v2, p->start, p->end);
    pthread_mutex_lock(&(p->b->m));
    p->b->prodScalare += sum;
    printf("nuova somma: %d\n",p->b->prodScalare);
    pthread_mutex_unlock(&(p->b->m));
    pthread_exit(NULL);
}

