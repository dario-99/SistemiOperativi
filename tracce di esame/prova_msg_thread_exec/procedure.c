#include "procedure.h"
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

static int ds_rts;
static int ds_ots;
void initServiceQueues(){
    key_t chiave_a = ftok(FTOK_PATH, FTOK_CHAR_O);
    key_t chiave_b = ftok(FTOK_PATH, FTOK_CHAR_R);
    ds_ots = msgget(chiave_a, IPC_CREAT | 0664);
    ds_rts = msgget(chiave_b, IPC_CREAT | 0664);
}
void syncSend(msg *m, int queue){
    msg_sync m1,m2;
    m1.type = getpid();
    strcpy(m1.messaggio, "RTS");
    msgsnd(ds_rts, (void*)&m1, sizeof(msg_sync) - sizeof(long), 0);
    printf("messaggio RTS inviato: %ld, %s\n", m1.type, m1.messaggio);
    msgrcv(ds_ots, (void*)&m2, sizeof(msg_sync) - sizeof(long), getpid(), 0);
    printf("messaggio OTS ricevuto: %ld, %s\n", m2.type, m2.messaggio);
    msgsnd(queue, (void*)m, sizeof(msg) - sizeof(long), 0);
}
void syncRcv(msg *m, int queue, int type){
    msg_sync m1,m2;
    msgrcv(ds_rts, (void*)&m1, sizeof(msg_sync) - sizeof(long), 0, 0);
    printf("msg rts ricevuto = %ld, %s\n", m1.type, m1.messaggio);
    m2.type = m1.type;
    strcpy(m2.messaggio, "OTS");
    msgsnd(ds_ots, (void*)&m2, sizeof(msg_sync) - sizeof(long), 0);
    printf("messaggio OTS inviato = %ld, %s\n", m2.type, m2.messaggio);
    msgrcv(queue, (void*)m, sizeof(msg) - sizeof(long), type, 0);
    printf("messaggio ricevuto = (%d, %d)\n", m->v[0], m->v[1]);
}
void removeServiceQueues(){
    msgctl(ds_rts, IPC_RMID, NULL);
    msgctl(ds_ots, IPC_RMID, NULL);
}

void* server(void* par){
    msg m;
    param* p = (param*)par;
    for(int i=0; i<msg_to_read; i++){
        syncRcv(&m, p->coda, RISULTATO_TYPE);
        int somma;
        somma = m.v[0] + m.v[1];
        printf("Somma dei due numeri = %d\n", somma);
    }
    pthread_exit(NULL);
}
void client(int ds_ris){
    msg m;
    m.type = 1;
    //suppongo sia stata chiamata srand()
    for(int i = 0; i < msg_to_send; i++){
        m.v[0] = rand()%100;
        m.v[1] = rand()%100;
        syncSend(&m, ds_ris);
        printf("Client inviati (%d, %d)\n", m.v[0], m.v[1]);
    }
}