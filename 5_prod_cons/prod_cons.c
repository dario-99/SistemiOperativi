#include <stdio.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include "semafori.h"
#include "procedure.h"

int main(){
    //CREAZIONE SHM
    key_t chiave = IPC_PRIVATE;
    int ds_shm = shmget(chiave, sizeof(int), IPC_CREAT | 0664);
    if(ds_shm < 0){
        perror("Err shm\n");
        exit(1);
    }
    int *p;
    p = (int*)shmat(ds_shm, NULL, 0);
    if(p == (void*) -1){
        perror("err shmat\n");
        exit(1);
    }

    //SEMAFORI
    key_t chiavesem = IPC_PRIVATE;
    int ds_sem = semget(chiavesem, 2, IPC_CREAT | 0664);
    if(ds_shm < 0){
        perror("Err sem\n");
        shmctl(ds_shm, IPC_RMID, NULL);
        exit(1);
    }
    //INIT SEMAFORI
    semctl(ds_shm, SPAZIO_DISPONIBILE, SETVAL, 1);
    semctl(ds_shm, MESSAGIO_DISPONIBILE, SETVAL, 0);
    
    //creo processo PROD e CONS
    int pid = fork();
    if(pid == 0){
        printf("sono il consumatore\n");
        consumatore(p, ds_sem);
        exit(1);
    }
    pid = fork();
    if(pid == 0){
        printf("sono il produttore\n");
        produttore(p,ds_sem);
        exit(1);
    }
    wait(NULL);
    wait(NULL);

    shmctl(ds_shm,IPC_RMID, NULL);
    semctl(ds_sem, SPAZIO_DISPONIBILE, IPC_RMID);
    semctl(ds_sem, MESSAGIO_DISPONIBILE, IPC_RMID);
    return 0;
}