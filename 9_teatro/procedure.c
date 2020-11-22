#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "procedure.h"
#include "semafori.h"


void visualizzatore(int sem_id, posto* vett, int* posti_disp){
    int cont = 0;
    while(1){
        sleep(1);
        //Wait_Sem(sem_id, MUTEX);
        //Wait_Sem(sem_id, SEM_VETT_POSTI);
        system("clear");
        printf("POSTI DISPONIBILI: %d\n", *posti_disp);
        int i ;
        for(i = 0; i < MAX_POSTI; i++){
            printf("\tN. POSTO: %d\n", i);
            if(vett[i].stato == LIBERO)
                printf("\t   STATO: %s\n", "LIBERO");
            else if(vett[i].stato == OCCUPATO){
                printf("\t   STATO: %s\n", "OCCUPATO");  
                printf("\t   ID PROPRIETARIO: %d\n", vett[i].id_cliente);   
            }
            else
                printf("\t   STATO: %s\n", "IN AGGIORNAMENTO");
        }
        //Signal_Sem(sem_id, MUTEX);
        //Signal_Sem(sem_id, SEM_VETT_POSTI);
        cont++;
    }
}
void cliente(int sem_id, posto* vett, int* posti_disp){
    int num_posti, s;

    //sleep  0 to 5 s
    srand(time(NULL));
    s = rand()%6;
    

    //numero di posti da occupare
    srand(time(NULL));
    num_posti = rand()%4+1;
 
    //CONTROLLO CHE CI SIANO POSTI DISPONIBILI
    Wait_Sem(sem_id,MUTEX); //aspetto l'accesso alla variabile globale
    Wait_Sem(sem_id, SEM_VETT_POSTI);   //aspetto l'accesso al vettore dei posti
    if(*posti_disp >= num_posti){
        *posti_disp -= num_posti;
        printf("%d posti disponibili attuali %d\n",getpid(), *posti_disp);
        //OCCUPO I POSTI
        //SEZIONE CRITICA OCCUPO N POSTI
        int i = 0;
        while(num_posti != 0){
            if(vett[i].stato == LIBERO){
                vett[i].stato = IN_AGGIORNAMENTO;
                sleep(1);
                printf("CLIENTE %d occupo posto %d\n",getpid(), i);
                vett[i].stato = OCCUPATO;
                vett[i].id_cliente = getpid();
                num_posti--;
            }
            i++;
        }
    }
    else{
        printf("NO POSTI DISPONIBILI\n");
    }
    Signal_Sem(sem_id, SEM_VETT_POSTI);
    Signal_Sem(sem_id, MUTEX);
}