#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "test.h"
int a = 10;

int main(){
    pthread_t threads[10];
    pthread_mutex_t *m = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

    pthread_mutex_init(m, NULL);
    for(int i = 0; i<10; i++){
        pthread_create(&threads[i], NULL, fun, (void*)m);
    }

    for(int i =0 ; i< 10; i++){
        pthread_join(threads[i],NULL);
    }
    pthread_mutex_destroy(m);
    
    pthread_exit(NULL);
    free(m);
    return 0;
}