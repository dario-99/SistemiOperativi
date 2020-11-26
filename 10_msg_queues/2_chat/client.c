#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "msglib.h"


int main(){
    key_t chiave;
    int ds_msgq;
    chiave = ftok(FTOK_PATH, FTOK_CHAR);
    ds_msgq = msgget(chiave, IPC_CREAT | 0664);
    if(ds_msgq < 0){
        perror("Err msgget()\n");
        exit(1);
    }
    login(ds_msgq);
    int pid;
    int process = getpid();
    pid = fork();
    if(pid == 0){
        //FIGLIO RECIEVE
        sendMsg(ds_msgq, process);
        kill(process ,SIGKILL);
        exit(0);
    }
    else if(pid > 0){
        //PADRE INPUT E SEND
        recMsg(ds_msgq, process);
    }
    return 0;
}