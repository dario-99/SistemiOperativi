#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "procedure.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>



int main(){
    int ds_sem = semget(IPC_PRIVATE, 3, IPC_CREAT | 0664);
    int ds_shm = shmget(IPC_PRIVATE, sizeof(buff), IPC_CREAT | 0664);

    buff *b = (buff*)shmat(ds_shm, NULL, 0);
    pid_t pid;

    semctl(ds_sem, MUTEX, SETVAL, 1);
    semctl(ds_sem, SPAZIO_DISP, SETVAL, SIZE);
    semctl(ds_sem, MSG_DISP, SETVAL, 0);

    for(int i = 0; i<10; i++){
        pid = fork();

        if(pid == 0){
            if(i%2 == 0){
                srand(time(NULL) * getpid());
                for(int j = 0; j<5; j++){
                    int val = rand()%100;
                    produci(ds_sem, b, val);
                    printf("Produttore #%d = %d\n", getpid(), val);
                }
                exit(0);
            }
            else{
                for(int j = 0; j < 5; j++){
                    printf("Inizio Figlio consumatore #%d\n", getpid());
                    int val = consuma(ds_sem, b);
                    printf("Consumatore #%d = %d\n",getpid(), val);
                }
                exit(0);
            }
        }       
    }
    for(int i= 0; i<10; i++){
        wait(NULL);
    }
    semctl(ds_sem, MUTEX, IPC_RMID, NULL);
    semctl(ds_sem, SPAZIO_DISP, IPC_RMID, NULL);
    semctl(ds_sem, MSG_DISP, IPC_RMID, NULL);
    shmctl(ds_shm, IPC_RMID, NULL);
    exit(0);
}