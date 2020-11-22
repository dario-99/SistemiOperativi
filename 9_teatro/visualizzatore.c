#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#include "procedure.h"
#include "semafori.h"



int main(){
    key_t chiave_vett = ftok(FPATH_VETT, FCHAR_VETT);
    key_t chiave_posti = ftok(FPATH, FCHAR);
    key_t chiave_sem = ftok(FPATH, FCHAR);
    int ds_vet = shmget(chiave_vett, (MAX_POSTI) * sizeof(posto), IPC_CREAT | 0664);
    if(ds_vet < 0){
        perror("err shmget VISUALIZZATORE\n");
        exit(1);
    }
    int ds_posti = shmget(chiave_posti, sizeof(int), IPC_CREAT | 0664);
    if(ds_posti < 0){
        perror("ERR shmget num posti\n");
        exit(1);
    }
    int ds_sem = semget(chiave_sem, 2, IPC_CREAT | 0664);
    if(ds_sem < 0){
        perror("errore semget VISUALIZZATORE \n");
        exit(1);
    }
    posto* vett = (posto*) shmat(ds_vet, NULL, 0);
    if(vett == (void*) -1){
        perror("errore shmat VISUALIZZATORE \n");
        exit(1);
    }
    int* posti_disp = (int*) shmat(ds_posti, NULL, 0);
    if(posti_disp == (void*) -1){
        perror("errore shmat VISUALIZZATORE \n");
        exit(1);
    }
    visualizzatore(ds_sem, vett, posti_disp);
    printf("END VISUALIZZATORE\n");
    return 0;
}