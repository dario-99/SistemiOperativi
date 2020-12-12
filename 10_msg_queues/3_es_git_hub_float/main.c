#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "procedure.h"

int main(){
    key_t chiave_msg;
    pid_t pid;
    int ds_msg, status, i;

    chiave_msg = ftok(FTOK_PATH, FTOK_CHAR);

    ds_msg = msgget(chiave_msg, IPC_CREAT | 0664);
    if(ds_msg < 0){
        perror("Err msgget\n");
        exit(1);
    }

    pid = fork();
    if(pid == 0){
        execl("./p1", "p1", NULL);
        perror("err exec p1\n");
        exit(1);
    }
    else if(pid < 0){
        perror("err fork p1\n");
        exit(1);
    }

    pid = fork();
    if(pid == 0){
        execl("./p2", "p2", NULL);
        perror("err exec p2\n");
        exit(1);
    }
    else if(pid < 0){
        perror("err fork p2\n");
        exit(1);
    }

    pid = fork();
    if(pid == 0){
        execl("./p3", "p3", NULL);
        perror("err exec p3\n");
        exit(1);
    }
    else if(pid < 0){
        perror("err fork p3\n");
        exit(1);
    }

    for (i = 0; i < 3; i++)
    {
        pid = wait(&status);
        printf("Figlio #%d morto con status %d\n", pid, status);
    }

    //deallocazione
    msgctl(ds_msg, IPC_RMID, NULL);
}