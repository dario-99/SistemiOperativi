#include "procedure.h"
#include <pthread.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
int main(){
    initServiceQueues();
    printf("Server STart\n");
    //prendo la coda con ftok
    //suppongo che le code di servizio siano state inizializzate
    key_t chiave = ftok(FTOK_PATH, FTOK_CHAR_RIS);
    int ds_msg = msgget(chiave, IPC_CREAT | 0664);
    pthread_t thread[NUM_SERVER];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    param *p = malloc(sizeof(param)); 
    p->coda = ds_msg;
    for(int i = 0; i < NUM_SERVER; i++){
        if(pthread_create(&thread[i], &attr, server, (void*)p) != 0){
            printf("Errore pthreadcreate\n");
            exit(1);
        }
    }

    for(int i = 0; i<NUM_SERVER; i++){
        pthread_join(thread[i], NULL);
    }
    free(p);
    pthread_attr_destroy(&attr);
    exit(0);
}
