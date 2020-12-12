#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <time.h>
#include "procedure.h"
#include "semafori.h"

void inizio_lettura(int ds_sem, buffer* buf){
    Wait_Sem(ds_sem, MUTEX_L);
    buf->num_lettori = buf->num_lettori + 1;
    if(buf->num_lettori == 1)
        Wait_Sem(ds_sem, SYNCH);
    Signal_Sem(ds_sem, MUTEX_L);
}
void fine_lettura(int ds_sem, buffer* buf){
    Wait_Sem(ds_sem, MUTEX_L);
    buf->num_lettori = buf->num_lettori - 1;
    if(buf->num_lettori == 0){
        Signal_Sem(ds_sem, SYNCH);
    }
    Signal_Sem(ds_sem, MUTEX_L);
}
void inizio_scrittura(int ds_sem, buffer* buf){
    Wait_Sem(ds_sem, SYNCH);
}
void fine_scrittura(int ds_sem, buffer* buf){
    Signal_Sem(ds_sem, SYNCH);
}
void lettore(int ds_sem, buffer* buf){
    inizio_lettura(ds_sem, buf);
    sleep(3);
    printf("Lettore %d: \n",getpid());
    printf("\tval1: %d\n",buf->val_1);
    printf("\tval2: %d\n", buf->val_2);
    fine_lettura(ds_sem, buf);
}
void scrittore(int ds_sem, buffer* buf){
    inizio_scrittura(ds_sem, buf);
    srand(time(NULL) * getpid());
    int rand1 = rand() % 10;
    int rand2 = rand() % 10;
    sleep(1);
    buf->val_1 = rand1;
    buf->val_2 = rand2;
    printf("SCRITTORE scrivo %d e %d\n", rand1, rand2);
    fine_scrittura(ds_sem,buf);
}