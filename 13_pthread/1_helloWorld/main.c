#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void* printf_hello(void* i){
    int l = (int)i;
    printf("Hello world #%d\n", l);
    pthread_exit(0);
}
int main(){
    pthread_t threads[NUM_THREADS];
    int i, rc;
    for(i = 0; i<NUM_THREADS; i++){
        printf("creazione thread %d\n", i);
        rc = pthread_create(&threads[i], NULL, printf_hello, (void*)i);
    }
    pthread_exit(NULL);
}