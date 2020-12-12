#include "procedure.h"
#include "utils.h"
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

static void printmsg(messaggio *msg){
    int i;
    printf("\t[TYPE] = %ld\n", msg->type);
    printf("\t[STRINGA] = %s\n", msg->stringa);
    printf("\t[VETT] = ");
    for (i = 0; i < NUM_I; i++)
    {
        printf("%d ", msg->vett[i]);
        if(i == NUM_I - 1)
            printf("\n");
    }
    printf("\t[SUM] = %d\n", msg->sum);
}
void generatore(int ds_msg){
    int i;
    messaggio msg;
    msg.type = GEN;
    rand_string(msg.stringa, NUM_C-1);
    for(i=0; i<NUM_I; i++){
        msg.vett[i] = rand()%(MAX_I+1);    //[0,MAX_I]
    }
    msg.sum = 0;
    //send the msg
    msgsnd(ds_msg, (void*)&msg, sizeof(messaggio) - sizeof(long), 0);
    printf("[GENERATORE %d]\n", getpid());
    printmsg(&msg);
}

int filtro(int ds_msg){
    int err;
    messaggio msg;
    //if there's no message on the queue return -1 (check with IPC_NOWAIT)
    err = msgrcv(ds_msg, (void*)&msg, sizeof(messaggio) - sizeof(long), GEN, IPC_NOWAIT);
    if(err < 0)
        return -1;
    //finds the first occurence of char ${KEY_FILTRO}
    if(strchr(msg.stringa, KEY_FILTRO) == (char*)NULL){
        //key not found
        msg.type = FIL;
        msgsnd(ds_msg, (void*)&msg, sizeof(messaggio) - sizeof(long), 0);
        printf("[FILTRO] passo la stringa: %s\n", msg.stringa);
        return 0;
    }
    return 1;
}
//chk of the msg with type == FIL, sums the string and the int array and sets the sum field, set type = CHK
int checksum(int ds_msg){
    int err;
    messaggio msg;
    
    err = msgrcv(ds_msg, (void*)&msg, sizeof(messaggio) - sizeof(long), FIL, IPC_NOWAIT);
    if(err < 0)
        return -1;
    msg.type = CHK;
    msg.sum = sum_string(msg.stringa) + sum_integers(msg.vett, NUM_I);
    msgsnd(ds_msg, (void*)&msg, sizeof(messaggio) - sizeof(long), 0);
    printf("[CHECKSUM] = %d\n",msg.sum);
    return 0;
}
//prints the msg with type == CHK
int visualizzatore(int ds_msg){
    int err;
    messaggio msg;
    err = msgrcv(ds_msg, (void*)&msg, sizeof(messaggio) - sizeof(long), CHK, IPC_NOWAIT);
    if(err < 0)
        return -1;
    //print the msg
    printf("[VISUALIZZATORE]\n");
    printmsg(&msg);
    return 0;
}