#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "procedure.h"

int main(){
    key_t chiave_shm, chiave_sem;
    int ds_shm, ds_sem;
    int i;//iteratrice
    //shm
    chiave_shm = IPC_PRIVATE;
    ds_shm = shmget(chiave_shm, sizeof(coda), IPC_CREAT | 0664);
    if(ds_shm < 0){
        perror("Err shmget\n");
        exit(1);
    }
    coda* c = (coda*)shmat(ds_shm, NULL, 0);
    init_struct(c);
    //sem
    chiave_sem = IPC_PRIVATE;
    ds_sem = semget(chiave_sem, 4, IPC_CREAT | 0664);
    if(ds_sem < 0){
        perror("err semget\n");
        exit(1);
    }
    semctl(ds_sem, SPAZIO_DISP, SETVAL, SIZE);
    semctl(ds_sem, MSG_DISP, SETVAL, 0);
    semctl(ds_sem, MUTEX_P, SETVAL, 1);
    semctl(ds_sem, MUTEX_C, SETVAL, 1);

    //creazione figli
    pid_t pid;

    for(i = 0; i< NUM_PROD; i++){
        pid = fork();
        if(pid == 0){
            produci(ds_sem, c);
            //figlio esce
            exit(0);
        }
    }
    sleep(10);
    for(i = 0; i< NUM_CONS; i++){
        pid = fork();
        if(pid == 0){
            consuma(ds_sem, c);
            //figlio esce
            exit(0);
        }
    }
    

    for(i = 0; i<NUM_PROD + NUM_CONS; i++){
        wait(NULL);
    }

    //deallocazione
    shmctl(ds_shm, IPC_RMID, NULL);
    for(i=0; i<4; i++){
        semctl(ds_sem, i, IPC_RMID,NULL);
    }
}