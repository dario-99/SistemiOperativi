#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "header.h"

int coda_risultati;

#define NUM_THREADS_OPERANDI    2
#define NUM_THREADS_CALCOLO     3

void dealloco_monitor(MonitorOperandi* m){
        pthread_mutex_destroy(&(m->mutex));
        pthread_cond_destroy(&(m->msg_disp));
        pthread_cond_destroy(&(m->spazio_disp));
}

int main(){

        pthread_attr_t attr;
        pthread_t threads_operandi[NUM_THREADS_OPERANDI];
        pthread_t threads_risultati;
        pthread_t threads_calcolo[NUM_THREADS_CALCOLO];
        pid_t pid;
        int i;
        srand(time(NULL)*getpid());

        // Creazione coda risultati
        //key_t chiave_ris = ftok(FTOK_PATH_RIS, FTOK_CHAR_RIS);
        coda_risultati = msgget(IPC_PRIVATE, IPC_CREAT | 0664);/* TBD */
        printf("Coda coda_risultati create con desc: %d\n", coda_risultati);
    
        initServiceQueues();
        //creazione di una istanza di struttura monitor per gli operandi
        // MonitorOperandi sarà usato dai thread generazione operandi
        MonitorOperandi * pc_op = (MonitorOperandi*)malloc(sizeof(MonitorOperandi));/* TBD */
        if(pc_op == NULL){
                perror("ERR MALLOC\n");
        }
        //inizializzazione mutex e condition
        /* TBD */
        if(pthread_mutex_init(&(pc_op->mutex), NULL) < 0){
                perror("errore mutex init\n");
        }
        if(pthread_cond_init(&(pc_op->msg_disp), NULL) < 0)
                perror("err cond\n");
        if(pthread_cond_init(&(pc_op->spazio_disp), NULL) < 0){
                perror("err cond\n");
        }
        //inizializzazione delle variabili di stato
        /* TBD */
        pc_op->coda = 0;
        pc_op->testa = 0;
        pc_op->num_msg = 0;
        printf("coda = %d\n", pc_op->coda);
        //impostazione dei thread come joinable
        /* TBD */
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        // genero processo prelievo risultati
        /* TBD */
        pid = fork();
        if(pid == 0){
                preleva_risultati(coda_risultati);
                exit(1);
        }
        else if(pid < 0){
                perror("err fork prelievo\n");
                exit(1);
        }
        // genero thread generazione operandi
        /* TBD */
        for(i=0; i<NUM_THREADS_OPERANDI; i++){
                if(pthread_create(&threads_operandi[i], &attr, genera_operandi, pc_op) != 0){
                        perror("errore thread create\n");
                }
        }
        // genero thread di calcolo
        /* TBD */
        sleep(10);
        for(i=0; i<NUM_THREADS_CALCOLO; i++){
                if(pthread_create(&threads_calcolo[i], &attr, calcola, pc_op) != 0){
                        perror("Err pthread create\n");
                }
        }
        /* TBD:  Join threads a wait processo*/
        for(i=0; i< NUM_THREADS_CALCOLO; i++){
                pthread_join(threads_calcolo[i], NULL);
        }
        
        for(i=0; i< NUM_THREADS_OPERANDI; i++){
                pthread_join(threads_operandi[i], NULL);
        }
        wait(NULL);
        /*deallocazione risorse*/	
        /* TBD */
        pthread_attr_destroy(&attr);
        removeServiceQueues();
        msgctl(coda_risultati, IPC_RMID, NULL);
        dealloco_monitor(pc_op);
        free(pc_op);
        pthread_exit(NULL);
}

