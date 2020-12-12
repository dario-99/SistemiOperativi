#include "procedure.h"
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


//asynchronous send on the msg queue
int send_msg(int ds_msg, msg* m){
    int err;
    err = msgsnd(ds_msg, (void*)m, sizeof(msg) - sizeof(long), 0);
    if(err < 0){
        #ifdef DEBUG_M
        perror("Err send msg\n");
        #endif
        return -1;
    }
    return 0;
}

//read a msg from the msgqueue
int receive_msg(int ds_msg, msg* m){
    int err;
    err = msgrcv(ds_msg, (void*)&m, sizeof(msg) - sizeof(long), 0, 0);
    if(err < 0){
        #ifdef DEBUG_M
        perror("Err receive msg\n");
        #endif
        return -1;
    }
    printf("\tRICEVUTO MESSAGGIO\n");
    printf("[%d] = %f\n", m->PROCESS_ID, m->FLOAT_VALUE);
    return 0;
}

//generate a random float given the interval, returns -1 in case of invalid interval
int rand_float(float x1, float x2, float *res){
    if(x1 >= x2){
        #ifdef DEBUG_M
        perror("Err x1 >= x2\n");
        #endif
        return -1;
    }
    srand(time(NULL) * getpid());
    *res = (float) (rand()+x1)/(float)(RAND_MAX/x2);
    return 0;
}

//generate a msg given the pid=[1,2] and a float, returns -1 in case invalid pid
int generate_msg(int pid, msg* m){
    m->type = 1;
    int err;
    err = rand_float(i_sx, i_dx, &m->FLOAT_VALUE);
    if(err < 0){
        #ifdef DEBUG_M
        perror("Err rand_float\n");
        #endif
        return -1;
    }
    m->PROCESS_ID = pid;

    printf("[%d] = %f\n", m->PROCESS_ID, m->FLOAT_VALUE);
    return 0;
}