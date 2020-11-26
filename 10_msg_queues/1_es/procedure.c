#include "procedure.h"
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>


void sendMsg(int ds_msg,msg m1){
    printf("Msg inviato\n");
    msgsnd(ds_msg, (void*) &m1, sizeof(msg) - sizeof(long), 0);
}
void recieveMsg(int ds_msg){
    printf("attendo messaggio\n");
    msg m;
    msgrcv(ds_msg,(void*)&m, sizeof(msg) - sizeof(long), MSG_TYPE, 0);
    printf("Messaggio: \n");
    printf("TEXT: %s\n", m.text);
}