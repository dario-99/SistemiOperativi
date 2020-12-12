#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>   //include time.h per srand()

#include "prodcons.h"

int main()
{

    int shm_id = shmget(IPC_PRIVATE, sizeof(ProdCons), IPC_CREAT | 0664);/* TBD: Allocazione della struttura dati in shared memory */

    if (shm_id < 0)
    {
        perror("Errore creazione shared memory");
        exit(1);
    }

    ProdCons *p = (ProdCons*)shmat(shm_id, 0, 0);/* TBD: Attach della shared memory */

    if (p == (void *)-1)
    {
        perror("Errore attach shared memory");
        exit(1);
    }

    inizializza(p);

    /* TBD: Aggiungere codice per avviare Produttori e Consumatori */
    pid_t pid;
    int i, j;   //variabili iteratrici
    int val;   //valore prodotto casualmente
    //FORK PRODUTTORI
    for(i=0;i<5;i++){
        pid = fork();
        if(pid == 0){
            srand(getpid() * time(NULL));
            for(j=0; j<N_PRODUCI; j++){
                val = rand();
                produci(p, val);
                sleep(2);
            }
            exit(0);
        }
        else if(pid < 0){
            perror("ERR fork produttori\n");
            rimuovi(p);
            shmctl(shm_id, IPC_RMID, NULL);
            kill(0, SIGKILL);
            exit(1);
        }
    }
    
    //FORK CONSUMATORI
    for(i=0;i<5;i++){
        pid = fork();
        if(pid == 0){
            for(j=0; j<N_CONSUMA; j++){
                consuma(p);
                sleep(1);
            }
            exit(0);
        }
        else if(pid < 0){
            perror("ERR fork consumatori\n");
            rimuovi(p);
            shmctl(shm_id, IPC_RMID, NULL);
            kill(0, SIGKILL);
            exit(1);
        }
    }
    printf("[%d] Processo padre in attesa...\n", getpid());

    for (i = 0; i < 10; i++)
    {
        wait(NULL);
    }

    printf("[%d] Terminazione\n", getpid());

    rimuovi(p);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
