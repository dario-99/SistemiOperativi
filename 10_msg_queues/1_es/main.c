#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "procedure.h"


int main(){
    key_t chiave_msg;
    int ds_msg;

    chiave_msg = IPC_PRIVATE;
    ds_msg = msgget(chiave_msg, IPC_CREAT | 0664);
    if(ds_msg < 0){
        perror("ERR msgget\n");
        exit(1);
    }

    //creazione processi
    int pid = fork();
    if(pid == 0){
        //figlio
        recieveMsg(ds_msg);
        exit(0);
    }
    else if(pid > 0){
        //padre
        msg m1;
        strcpy(m1.text, "Ciao Figlio");
        m1.type = MSG_TYPE;
        sendMsg(ds_msg, m1);
    }
    else{
        exit(1);
    }
    wait(NULL);

    //ELIMINO CODA
    msgctl(ds_msg,IPC_RMID, 0);
    exit(0);
}