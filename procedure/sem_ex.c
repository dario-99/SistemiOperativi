#include "procedure.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(){
    //allocare e init shm
    key_t k_shmem = IPC_PRIVATE;
    int id_shmem = shmget(k_shmem, sizeof(int), IPC_CREAT | 0664);
    if(id_shmem<0){
        perror("Errore creazione shmem\n");
        exit(1);
    }
    int* ptr = (int*)shmat(id_shmem, NULL,0);
    if(ptr == (void*)-1){
        perror("Errore shmat\n");
        exit(1);
    }

    //allocare e init semafori
    key_t k_sem = IPC_PRIVATE;
    int id_sem = semget(k_sem, 1, IPC_CREAT | 0664);
    semctl(id_sem, 0, SETVAL, 1); //inizializzo il semaforo con semctl, poiche' sara' un mutex lo init a 1
    printf("sem %d inizializzatp\n",id_sem);
    *ptr = 0;   //inizializzo a 0 il puntatore a shm
    printf("Valore iniziale della shm: %d\n", *ptr);

    //generare i processi figli
    int i;
    for(i=0;i<2;i++){
        pid_t pid = fork();
        if(pid < 0){
            perror("Errore creazione processo FORK\n");
            exit(1);
        }
        if(pid == 0){
            int j;
            for(j=0;j<100;j++){
                //INIZIO SEZIONE CRITICA
                //operare sulla sezione critica (wait_sem e signal_sem)
                wait_sem(id_sem,0);
                //processo figlio
                printf("Sono il figlio: %d\n",getpid());
                printf("processo %d ha letto il valore\n",i);
                (*ptr)++;
                printf("processo %d ha incrementato\n",i);
                signal_sem(id_sem,0);
                //FINE SEZIONE CRITICA
            }
            exit(0);
        }
    }

    //PROCESSO PADRE
    for(i = 0; i<2; i++){
        wait(NULL); 
    }
    printf("valore shm finale: %d\n", *ptr);
    //deallocazione shm e deallocazione sem
    shmctl(id_shmem, IPC_RMID, 0);
    semctl(id_sem, 0, IPC_RMID);

    return 0;
}