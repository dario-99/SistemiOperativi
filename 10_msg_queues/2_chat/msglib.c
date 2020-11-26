#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "msglib.h"

void login(int ds_msqd){
    msg m, m_ack;
    m.id = getpid();
    strcpy(m.msg, "LOGIN REQUEST");
    m.type = CLIENT_MSG;
    //SEND SCINCRONA
    msgsnd(ds_msqd, (void*)&m, sizeof(msg) - sizeof(long), 0);
    msgrcv(ds_msqd, (void*)&m_ack, sizeof(msg) - sizeof(long), getpid(), 0);
}
void sendMsg(int ds_msqd, int pid){
    msg m;
    m.id = pid;
    m.type = CLIENT_MSG;
    while(1){
        int cont = 0;
        char ch = getchar();
        while(ch!='\n' && cont<MAX_SIZE)
        { 
            m.msg[cont++]=ch;
            ch=getchar();
        }
        m.msg[cont] = '\0';
        if(strcmp(m.msg, "exit") == 0){
            break;
        }
        else
            msgsnd(ds_msqd, (void*)&m, sizeof(msg) - sizeof(long), 0);
    }
}
void recMsg(int ds_msqd,int pid){
    msg m;
    while(1){
        msgrcv(ds_msqd, (void*)&m, sizeof(msg) - sizeof(long), pid, 0);
        printf("[%d] %s\n",m.id,m.msg);
    }
}
int find(int* v,int l,  int k){
    int i;
    for(i= 0; i< l; i++){
        if(v[i] == k){
            return 1;
        }
    }
    return 0;
}