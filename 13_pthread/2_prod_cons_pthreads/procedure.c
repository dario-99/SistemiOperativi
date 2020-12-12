#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include "procedure.h"
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>


void Produci(struct ProdCons *pc, msg m){
    //enter monitor
    pthread_mutex_lock(&pc->mutex);
    while(pc->ok_produzione == 0){
        pthread_cond_wait(&pc->ok_prod_cv);
    }

    //produzione
    pc->mess = m;

    //update var cond

    //signal consumatori
    pthread_cond_signal(&pc->mutex);

    //leave monitor
    pthread_mutex_unlock(&pc->mutex);
}
void Consuma(struct ProdCons *pc, msg m){
    pthread_mutex_lock(&pc->mutex);

    while(pc->ok_consumo == 0){
        pthread_cond_wait(&pc->ok_cons_cv, &pc->mutex);
    }
    printf("val cons: %d\n", pc->mess);

    pc->ok_produzione = 1;
    pc->ok_consumo = 0;

    pthread_cond_signal(&pc->)
}
void* produttore(void* p){
    
}
void* consumatore(void* p){
    struct ProdCons *pc = (struct Prodcons *)p;
    int i;
    for(i=0;i<3;i++){
        struct timeval t1;
        struct timezone t2;
        getitimeofday(&t1,&t2);

        msg m = t1.tv_usec;
        Produci(pc, m);
    }
    pthread_exit(0);
}