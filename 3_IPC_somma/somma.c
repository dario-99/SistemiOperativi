#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
int main(){
    key_t chiave = IPC_PRIVATE;
    int id = shmget(chiave,sizeof(int),IPC_CREAT|IPC_EXCL|0664);
    if(id>0){
        int* p= (int*)shmat(id,NULL,0);
        if(p == (void*)-1){
            printf("errore creazione shm\n");
            exit(1);
        }
        //creo processo figlio che modifica il valore della string
        *p = 0;
        int i = 0;
        int pid;
        for(i = 0; i<5; i++){
            pid = fork();
            if(pid == 0){
                (*p)++;
            }
        }
        if(pid>0){
            wait(NULL);
            printf("var p=%d\n",*p);
        }
        shmdt(p);
        shmctl(id,IPC_RMID,NULL);
    }
    else{
        printf("errore creazione id shm\n");
        exit(1);
    }
}