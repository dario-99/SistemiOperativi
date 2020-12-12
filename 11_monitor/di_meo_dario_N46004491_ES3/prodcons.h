#ifndef _PRODCONS_H_
#define _PRODCONS_H_

#include "monitor_hoare.h"

#define DIM 10

typedef struct {
    long vettore[DIM];
    int testa;
    int coda;
    /* TBD: Definire il Monitor e le altre variabili per la sincronizzazione */
    int totale_elementi;
    Monitor m;
} ProdCons;

/* TBD: Definire delle macro per identificare le variabili condition */
#define SPAZIO_DISP 0
#define MSG_3DISP 1

#define N_CONSUMA 3 //numero di msg da consumare
#define N_PRODUCI 9 //numero di msg da produrre


void inizializza(ProdCons * p);
void consuma(ProdCons * p);
void produci(ProdCons * p, int val);
void rimuovi(ProdCons * p);

#endif
