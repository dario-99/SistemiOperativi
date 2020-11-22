#include "procedure.h"
#include <stdio.h>
#include <errno.h>
int wait_sem(int id_sem, int numsem){
    struct sembuf sem_buf;
    int err;    //contiene il risultato della chiamata semop

    sem_buf.sem_num = numsem;
    sem_buf.sem_flg = 0;
    sem_buf.sem_op = -1;
    err = semop(id_sem,&sem_buf,1); //semaforo rosso
    if(err<0){
        perror("errore nella wait_sem\n");
    }
    return err;
}
int signal_sem(int id_sem, int numsem){
    struct sembuf sem_buf;
    int err;    //contiene il risultato della chiamata semop

    sem_buf.sem_num = numsem;
    sem_buf.sem_flg = 0;
    sem_buf.sem_op = 1;
    err = semop(id_sem,&sem_buf,1); //semaforo verde
    if(err<0){
        perror("errore nella signal_sem\n");
    }
    return err;
}