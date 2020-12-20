#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define FTOK_PATH "./"
#define FTOK_CHAR_R 'd'
#define FTOK_CHAR_O 'c'
#define FTOK_CHAR_RIS 'g'

#define msg_to_send 4
#define msg_to_read 6
#define NUM_SERVER 2
#define NUM_CLIENT 3
#define RISULTATO_TYPE 1

typedef struct{
    long type;
    int v[2];
}msg;
typedef struct{
    long type;
    char messaggio[20];
}msg_sync;

typedef struct{
    int coda;

}param;
void initServiceQueues();
void syncSend(msg *m, int queue);
void syncRcv(msg *m, int queue, int type);
void removeServiceQueues();

void* server(void* par);
void client(int ds_ris);
#endif