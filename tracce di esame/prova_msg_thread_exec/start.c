#include <stdio.h>
#include "procedure.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/msg.h>

int main(){
    initServiceQueues();
    key_t chiave = ftok(FTOK_PATH, FTOK_CHAR_RIS);
    int ds_msg = msgget(chiave, IPC_CREAT | 0664);
    pid_t pid;
    for(int i = 0; i < NUM_CLIENT; i++){
        pid = fork();
        if(pid == 0){
            execl("./client", "./client", (char*)0);
            perror("non dovresti essere qui\n");
            exit(1);
        }
        else if(pid < 0){
            perror("Err fork\n");
            exit(1);
        }
    } 
    pid = fork();
    if(pid == 0){
        execl("./server", "./server", (char*)0);
        perror("non dovrei essere qui\n");
        exit(1);
    }
    else if(pid < 0){
        perror("errore fork server\n");
        exit(1);
    }
    for(int i = 0; i < NUM_CLIENT + 1; i++){
        pid = wait(NULL);
        printf("figlio #%d morto\n", pid);

    }
    msgctl(ds_msg, IPC_RMID, NULL);
    removeServiceQueues();
    return 0;
}