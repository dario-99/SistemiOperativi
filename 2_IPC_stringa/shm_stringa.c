#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    key_t chiave = IPC_PRIVATE;
    int id = shmget(chiave,sizeof("Hello World\0"),IPC_CREAT|IPC_EXCL|0664);
    printf("id shm:%d",id);
    if(id>0){
        char* p = (char*)shmat(id,NULL,0);
        if(p == (void*)-1){
            printf("errore creazione shm\n");
            exit(1);
        }
        //creo processo figlio che modifica il valore della string
        int pid = fork();
        if(pid == 0){
            strcpy(p,"hello woel");
            shmdt(p);
            exit(0);
        }
        else if(pid > 0){
            wait(NULL);
            printf("%s\n",p);
        }
        else{
            printf("errore creazione processo figlio!\n");
        }
        shmdt(p);
        shmctl(id,IPC_RMID,NULL);
    }
    else{
        printf("errore creazione id shm\n");
        exit(1);
    }
    return 0;
}