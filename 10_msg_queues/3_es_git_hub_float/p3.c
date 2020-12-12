#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "procedure.h"

void print(float* v, int n){
    int i =0;
    for(i=0; i<n; i++){
        printf("v[%i] = %f\n", i, v[i]);
    }
}

int main(){
    key_t chiave_msg;
    int ds_msg, i, err;

    chiave_msg = ftok(FTOK_PATH,FTOK_CHAR);
    ds_msg = msgget(chiave_msg, IPC_CREAT | 0664);
    if(ds_msg < 0){
        perror("Err p1 msgget\n");
        exit(1);
    }

    float m1 = 0;
    float m2 = 0;
    msg m;

    for(i = 0; i< 2*MSG_TO_SEND; i++){
        err = msgrcv(ds_msg, (void*)&m, sizeof(msg) - sizeof(long), 0, 0);
        if(err < 0){
            perror("err rcv msg p3\n");
            exit(1);
        }
        if(m.PROCESS_ID == 1){
            printf("FLOAT VALUE p1 = %f\n", m.FLOAT_VALUE);
            m1 += m.FLOAT_VALUE /MSG_TO_SEND;
        }
        else{
            printf("FLOAT VALUE p2 = %f\n", m.FLOAT_VALUE);
            m2 += m.FLOAT_VALUE / MSG_TO_SEND;
        }
    }

    //print media
    printf("media p1: %f\n", m1);
    printf("media p2: %f\n", m2);
    return 0;
}