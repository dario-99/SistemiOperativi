#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "procedure.h"
#include "semafori.h"


int main(){
    //creazione variabile condivisa dei POSTI LIBERI
    key_t chiaveNumPosti = ftok(FPATH, FCHAR);
    if(chiaveNumPosti < 0){
        perror("err chiave posti\n");
        exit(1);
    }
    int ds_posti = shmget(chiaveNumPosti, sizeof(int), IPC_CREAT | 0664);
    if(ds_posti < 0){
        perror("ERR shmget num posti\n");
        exit(1);
    }
    int* num_posti  = (int*)shmat(ds_posti, NULL, 0);
    *num_posti  = MAX_POSTI;
    printf("NUMERO POSTI INIZIALI %d\n",*num_posti);
    //creazione array condiviso
    key_t chiaveVettore = ftok(FPATH_VETT, FCHAR_VETT);
    if(chiaveVettore < 0 ){
        perror("ERR chiave vettore\n");
        exit(1);
    }
    //get descrittore risorsa
    int ds_vet = shmget(chiaveVettore, MAX_POSTI*sizeof(posto), IPC_CREAT | 0664);
    if(ds_vet < 0){
        perror("ERR shmget vettore\n");
        exit(1);
    }
    //ATTACH
    posto* vett = (posto*) shmat(ds_vet, NULL, 0);
    if(vett == (void*)-1){
        perror("err shmat\n");
        exit(1);
    } 
    //creazione SEMAFORI
    key_t chiave_sem = ftok(FPATH, FCHAR);
    int sem_id = semget(chiave_sem, 2, IPC_CREAT | 0664);
    if(sem_id < 0){
        perror("errore semget\n");
        exit(1);
    }
    semctl(sem_id, MUTEX, SETVAL, 1);
    semctl(sem_id, SEM_VETT_POSTI, SETVAL, 1);
    //INIT del vettore
    int i;
    for(i=0; i<MAX_POSTI; i++){
        vett[i].id_cliente = 0;
        vett[i].stato = LIBERO;
    }

    //FIglI
    int pid;
    /* for(i=0; i<NUM_VISUALIZZATORI; i++){
        pid = fork();
        if(pid == 0){
            execl("./visualizzatore","" ,(char*)0);
        }
    } */
    for(i = 0; i< NUM_CLIENTI; i++){
        pid = fork();
        if(pid == 0){
            printf("SONO IL CLIENTE CON PID %d\n", getpid());
            cliente(sem_id, vett, num_posti);
            printf("ESCE CLIENTE %d\n", getpid());
            exit(0);
        }
    }
    for(i = 0; i< NUM_CLIENTI /* + NUM_VISUALIZZATORI */; i++){
        wait(NULL);
    }



    //dealloco le SHM
    shmctl(ds_vet, IPC_RMID, 0);
    //dealloco i semafori
    semctl(sem_id,0,IPC_RMID,NULL);
    semctl(sem_id,1,IPC_RMID,NULL);
    return 0; 
}