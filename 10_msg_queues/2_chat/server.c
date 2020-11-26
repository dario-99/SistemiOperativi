#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "msglib.h"

//il server si occupa dell'inizializzazione della coda, su cui aspetta le richieste di login
//RICHIESTA DI LOGIN:
//  1)   processo invia PID al server sulla CODA CONDIVISA usando ftok per creare la coda
//  2)   server num_utenti++
//  3)   server vett_client.push(pid)
//SEND MESSAGGIO
//  1)   msgsend N volte dove N e' il num_utenti ogni messaggio avra il tipo == vett_clienti[i]
//avra un vettore di utenti e una variabile con il numero di utenti
//

int main(){
    //INIT CODA 
    key_t chiave;
    int ds_msgq;
    chiave = ftok(FTOK_PATH, FTOK_CHAR);
    ds_msgq = msgget(chiave, IPC_CREAT | 0664);
    if(ds_msgq < 0){
        perror("Err msgget()\n");
        exit(1);
    }
    int clienti[MAX_CLIENT];
    int num_clienti = 0;
    msg m;
    printf("SERVER START\n");
    while(1){
        //REQUEST HANDLER
        //RECEIVE
        msgrcv(ds_msgq, (void*)&m, sizeof(msg) - sizeof(long), CLIENT_MSG, 0);
        printf("NEW MESSAGE\n");
        msg m1;
        if(find(clienti, num_clienti, m.id)){
            printf("New message to send\n");
            if(num_clienti <= 0){
                printf("Errore nessun utente\n");
                //invio messaggio di errore all' utente
                strcpy(m1.msg,"Error no one to send");
                m1.id = ID_SERVER;
                m1.type = m.id;
            }
            else{
                //Ok send
                int i;
                for(i = 0; i < num_clienti; i++){
                    msg m1;
                    m1.id = m.id;
                    strcpy(m1.msg, m.msg);
                    m1.type = clienti[i];
                    msgsnd(ds_msgq, (void*)&m1, sizeof(msg) - sizeof(long), 0);
                }
                printf("[%d] %s\n",m.id,m.msg);
                printf("Messaggio inviato a tutti i client\n");
            }
        }
        else{
            clienti[num_clienti++] = m.id;
            //SEND ACK
            m1.id = ID_SERVER;
            strcpy(m1.msg, "ACK");
            m1.type = m.id;
            msgsnd(ds_msgq, (void*)&m1, sizeof(msg) - sizeof(long), 0);
            printf("New client\n");
            printf("id: %d\n", m.id);
            printf("Num client: %d\n", num_clienti);
        }
    }
    //chiudo coda
    msgctl(ds_msgq, IPC_RMID, 0);
}