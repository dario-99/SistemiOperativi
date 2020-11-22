#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

int main(){
    key_t chiave = IPC_PRIVATE;    
    //stampo la chiave
    printf("chiave: %d\n",chiave);
    //shm un intero
    int ishm_id = shmget(chiave,sizeof(int),IPC_CREAT|0664);
    if(ishm_id>0){
        //ho creato una shm
        int* p = (int*)shmat(ishm_id,NULL, 0);
        if(p == (void*)-1){
            //assegnazione locazione di memoria
            printf("errore creazione shm\n");
            exit(1);
        }
        //creo un processo figlio e modifico
        *p = 10;
        int pid  = fork();
        if(pid == 0){
            //modifico il valore di p
            *p = 20;
            exit(0); 
        }
        else if(pid>0){
            wait(NULL);
            printf("*p= %d\n",*p);
        }
        else{
            printf("errore crezione processo figlio\n");
            exit(1);
        }
    }
    else{
        //non ho creato una shm
        printf("creazione IPC shm\n");
    }
    return 0;
}