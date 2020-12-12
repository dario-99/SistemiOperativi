#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "procedure.h"
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
int main(){
    key_t chiave_shm, chiave_sem;
    int ds_shm, ds_sem;
    buffer* buf;
    //creazione shm buffer
    chiave_shm = ftok(FTOK_PATH, FTOK_CHAR);
    if(chiave_shm < 0){
        perror("Errore chiave shm\n");
        exit(1);
    }
    ds_shm = shmget(chiave_shm, sizeof(buffer), IPC_CREAT | 0664);
    if(ds_shm < 0){
        perror("errore SHMGET\n");
        exit(1);
    }
    buf = shmat(ds_shm, NULL, 0);
    if(buf == (void*) -1){
        perror("errore SHMAT\n");
        exit(1);
    }
    //creazione sem
    chiave_sem = ftok(FTOK_PATH, FTOK_CHAR);
    if(chiave_sem < 0){
        perror("errore chiave sem\n");
        exit(1);
    }
    ds_sem = semget(chiave_sem, 2, IPC_CREAT | 0664);
    if(ds_sem < 0){
        perror("errore semget\n");
        exit(1);
    }

    //EFFETUO SCRITTURA
    int i;
    for(i = 0; i<SCRITTURE; i++){
        scrittore(ds_sem, buf);
    }

}