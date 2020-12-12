/*
    name: main
    descrizione: Main che si occupa di allocare le shm e i semafori, inizializzare e creare i processi con la fork exec, infine dealloca le IPC
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include "procedure.h"


int main(){
    //chiavi IPC
    key_t chiave_buf, chiave_sem;
    //descrittori IPC
    int ds_shm, ds_sem;
    //Puntatori alla shm
    void* buf;
    char *s;
    int *n_lett;
    srand(time(NULL)*getpid());
    int N = rand()%6 + 10;

    //allocazione shm per N+1 char e un int per NUM_LETTORI, poi con il punt a void* mi prendo i valori che mi servono
    //con l'aritmetica dei puntatori
    chiave_buf = ftok(FTOK_PATH, FTOK_CHAR);
    if(chiave_buf < 0){
        perror("ERR ftok shm main\n");
        exit(1);
    }
    ds_shm = shmget(chiave_buf, (N + 1) + sizeof(int), IPC_CREAT | 0664);
    if(ds_shm < 0){
        perror("ERR shmget main\n");
        exit(1);
    }
    buf = shmat(ds_shm, NULL, 0);
    if(buf == (void*)-1){
        perror("ERR shmat main\n");
        exit(1);
    }


    //allocazione semafori
    chiave_sem = ftok(FTOK_PATH, FTOK_CHAR);//posso usare i stessi parametri per la ftok() perche' sono due tipi di IPC diversi
    if(chiave_sem < 0){
        perror("ERR ftok sem main\n");
        exit(1);
    }
    ds_sem = semget(chiave_sem, 2, IPC_CREAT | 0664);
    if(ds_sem < 0){
        perror("ERR semget main\n");
        exit(1);
    }

    //inizializzazione shm gestendo con il punt a void
    s = (char*)buf;
    buf += N+1;
    n_lett = (int*)(buf);
    initBuffer(s, n_lett);

    //inizializzazione sem
    semctl(ds_sem, MUTEX_L, SETVAL, 1);
    semctl(ds_sem, SYNCH, SETVAL, 1);


    //converto N in una stringa
    char snum[3];   //3 = 2 char per cifra + \0
    sprintf(snum,"%d",N);
    
    //fork exec dei processi generatore, elaboratore e analizzatore
    pid_t pid;
    int i;
    for(i = 0; i < NUM_GENERATORI; i++){
        pid = fork();
        if(pid == 0){
            execl("./generatore","./generatore", snum, NULL);
            //non dovrei essere qui dopo l'execl
            perror("ERR exec generatore\n");
            exit(1);
        }
        else if(pid<0){
            perror("ERR fork generatore\n");
            exit(1);
        }
    }
    for(i = 0; i < NUM_ELABORATORI; i++){
        pid = fork();
        if(pid == 0){
            execl("./elaboratore", "./elaboratore", snum, NULL);
            //non dovrei essere qui dopo l'execl
            perror("ERR exec elaboratore\n");
            exit(1);
        }
        else if(pid<0){
            perror("ERR fork elaboratore\n");
            exit(1);
        }
    }
    for(i = 0; i < NUM_ANALIZZATORI; i++){
        pid = fork();
        if(pid == 0){
            execl("./analizzatore", "./analizzatore", snum, NULL);
            //non dovrei essere qui dopo l'execl
            perror("ERR exec analizzatore\n");
            exit(1);
        }
        else if(pid<0){
            perror("ERR fork analizzatore\n");
            exit(1);
        }
    }

    //wait dei processi figli
    for(i = 0; i < NUM_ANALIZZATORI + NUM_GENERATORI + NUM_ELABORATORI; i++){
        wait(NULL);
    }

    //deallocazione sem e shm
    semctl(ds_sem, MUTEX_L, IPC_RMID, NULL);
    semctl(ds_sem, SYNCH, IPC_RMID, NULL);
    shmctl(ds_shm, IPC_RMID, NULL);

    return 0;
}