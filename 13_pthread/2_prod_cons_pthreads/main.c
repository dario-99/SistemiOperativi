#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include "procedure.h"
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>

#define NUM_THREADS 6

int main(){
    int k;
    pthread_attr_t attr;
    pthread_t threads[NUM_THREADS];

    struct ProdCons *pc = malloc(sizeof(struct ProdCons));
    pthread_mutex_init(&pc->mutex, NULL);
    pthread_cond_init(&pc->ok_prod_cv, NULL);
    pthread_cond_init(&pc->ok_cons_cv, NULL);

    pc->ok_produzione = 1;
    pc->ok_consumo = 0;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for(k=0; k<NUM_THREADS; k++){
        if(k%2){
            pthread_create(&threads[k], &attr, consumatore, (void*)pc);
        }
        else{
            pthread_create(&threads[k], &attr, produttore, (void*)pc);
        }
    }


    for(k=0; k<NUM_THREADS; k++){
        pthread_join(threads[k], NULL);
    }

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&pc->mutex);
    pthread_cond_destroy(&pc->ok_cons_cv);
    pthread_cond_destroy(&pc->ok_prod_cv);

    free(pc);
    pthread_exit(NULL);
}