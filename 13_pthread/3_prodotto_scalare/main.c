#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "procedure.h"

int main(){
    pthread_t threads[NUM_THREAD];
    buf* b = (buf*)malloc(sizeof(buf));
    prod_s p[NUM_THREAD];



    initBuf(b);
    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);
    //init sruttura che passo ai singoli thread
    for(int i = 0; i < NUM_THREAD; i++){
        p[i].b = b;
        p[i].start = i*ELEM;
        p[i].end = (i+1)*ELEM;
        pthread_create(&threads[i], NULL, t_prodScalare, (void*)&p[i]);
    }
    
    
    //aspetto i thread
    for(int i=0; i<NUM_THREAD;i++){
        pthread_join((threads[i]), NULL);
    }

    printf("prodotto scalare = %d\n", b->prodScalare);

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken %f\n", elapsed);

    pthread_mutex_destroy(&(b->m));
    pthread_exit(NULL);
    free(b);
    return 0;
}