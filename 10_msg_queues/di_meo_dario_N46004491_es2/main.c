#include "procedure.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(){
    key_t chiave_msg;
    int ds_msg;
    pid_t pid;
    int i, j, status, err;
    int cont = 0;//counts the number of msg sent or processed by a child

    chiave_msg = IPC_PRIVATE;
    ds_msg = msgget(chiave_msg, IPC_CREAT | 0664);
    if(ds_msg < 0){
        perror("ERR msgget\n");
        exit(1);
    }

    for(i=0; i<NUMP_GENERATORI; i++){
        pid = fork();
        if(pid == 0){
            srand(time(NULL) * getpid());
            for(j=0; j<MSG_TO_SEND; j++){
                generatore(ds_msg);
            }
            exit(0);
        }
        else if(pid < 0){
            perror("ERR fork generatori\n");
            msgctl(ds_msg, IPC_RMID,NULL);
            exit(1);
        }
        usleep(100);//just not to mix the printf
    }
    sleep(2);
    for(i=0; i<NUMP_FILTRI; i++){
        pid = fork();
        if(pid == 0){
            for(j=0; j<MSG_TO_FIL; j++){
                err = filtro(ds_msg);
                if(err == 0)
                    cont++;//msg sent
                else if(err == -1){
                    printf("solo %d msg trovati da FILTRO\n", cont);
                    exit(1);
                }
            }
            printf("[FILTRO] %d msg inviati\n", cont);
            exit(0);
        }
        else if(pid < 0){
            perror("ERR fork filtro\n");
            msgctl(ds_msg, IPC_RMID,NULL);
            exit(1);
        }
    }
    sleep(2);
    for(i=0; i<NUMP_CHECK; i++){
        pid = fork();
        if(pid == 0){
            for(j=0; j<MSG_TO_CHK; j++){
                err = checksum(ds_msg);
                if(err == 0)
                    cont++;//msg sent
                else if(err == -1){
                    printf("[CHEKSUM] solo %d msg trovati\n", cont);
                    exit(1);
                }
            }
            printf("[CHEKSUM] %d msg inviati\n", cont);
            exit(0);
        }
        else if(pid < 0){
            perror("ERR fork checksum\n");
            msgctl(ds_msg, IPC_RMID,NULL);
            exit(1);
        }
    }
    sleep(2);
    for(i=0; i<NUMP_VISUALIZZATORI; i++){
        pid = fork();
        if(pid == 0){
            for(j=0; j<MSG_TO_VIS; j++){
                err = visualizzatore(ds_msg);
                if(err == 0)
                    cont++;//msg visualized
                else if(err == -1){
                    printf("[VISUALIZZATORE] solo %d msg trovati\n", cont);
                    exit(1);
                }
            }
            printf("[VISUALIZZATORE] %d msg stampati\n", cont);
            exit(0);
        }
        else if(pid < 0){
            perror("ERR fork visualizzatore\n");
            msgctl(ds_msg, IPC_RMID,NULL);
            exit(1);
        }
    }
    sleep(2);

    //wait childs
    for(i=0; i<NUMP_VISUALIZZATORI + NUMP_GENERATORI + NUMP_FILTRI + NUMP_CHECK; i++){
        pid = wait(&status);
        printf("Figlio #%d morto con status %d\n", pid, status);
    }
    //msgqueue deallocation
    msgctl(ds_msg, IPC_RMID,NULL);
    return 0;
}