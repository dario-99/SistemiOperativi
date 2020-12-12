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
    //INIT semafori
    semctl(ds_sem, MUTEX_L, SETVAL, 1);
    semctl(ds_sem, SYNCH, SETVAL, 1);
    //INIT buffer
    buf->num_lettori = 0;
    buf->val_1 = 0;
    buf->val_2 = 0;


    //CREAZIONE PROCESSI
    pid_t pid;
    int i;
    for(i = 0; i<NUM_LETTORI; i++){
        pid = fork();
        if(pid == 0){
            execl("./lettore","", NULL);
            perror("NON DOVREI ESSERE QUI, ERRORE LETTORE\n");
            exit(1);
        }
    }
    for(i = 0; i < NUM_SCRITTORI; i++){
        pid = fork();
        if(pid == 0){
            execl("./scrittore", "", NULL);
            perror("NON DOVREI ESSERE QUI, ERRORE SCRITTORE\n");
            exit(1);
        }
    }
    for(i = 0; i< NUM_SCRITTORI + NUM_LETTORI; i++){
        wait(NULL);
    }
    //free shm
    shmctl(ds_shm, IPC_RMID, NULL);
    //free sem
    semctl(ds_sem, MUTEX_L, IPC_RMID,NULL);
    semctl(ds_sem, SYNCH, IPC_RMID,NULL);
}