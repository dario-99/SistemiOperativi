#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "procedure.h"

int main(){
    key_t chiave_msg;
    int ds_msg, i, err;

    chiave_msg = ftok(FTOK_PATH,FTOK_CHAR);
    ds_msg = msgget(chiave_msg, IPC_CREAT | 0664);
    if(ds_msg < 0){
        perror("Err p1 msgget\n");
        exit(1);
    }

    msg m;
    float val;
    for(i = 0; i<MSG_TO_SEND; i++){
        err = generate_msg(1, &m);
        if(err < 0){
            perror("Err msg p1\n");
            exit(1);
        }
        send_msg(ds_msg, &m);
    }
    return 0;
}