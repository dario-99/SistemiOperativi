#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <time.h>
#include <stdlib.h>
#include "semafori.h"
#include "procedure.h"

void init_struct(coda* c){
    c->coda = 0;
    c->testa = 0;
}
void produci(int ds_sem, coda* c){
    Wait_Sem(ds_sem, SPAZIO_DISP);
    Wait_Sem(ds_sem, MUTEX_P);

    //SEZIONE CRITICA
    sleep(1);
    srand(time(NULL));
    int num = rand()%100;
    c->buff[c->testa] = num;
    c->testa = (++(c->testa))%SIZE;
    printf("produce %d\n", num);
    //FINE SEZIONE CRITICA

    Signal_Sem(ds_sem, MUTEX_P);
    Signal_Sem(ds_sem, MSG_DISP);
}
void consuma(int ds_sem, coda* c){
    Wait_Sem(ds_sem, MSG_DISP);
    Wait_Sem(ds_sem, MUTEX_C);

    //sezione critica
    sleep(1);
    int n = c->buff[c->coda];
    c->coda = (++(c->coda))%SIZE;
    printf("CONSUMO %d\n", n);
    //fine sezione critica

    Signal_Sem(ds_sem, MUTEX_C);
    Signal_Sem(ds_sem, SPAZIO_DISP);
}