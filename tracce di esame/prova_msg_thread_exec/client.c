#include <stdio.h>
#include <sys/msg.h>
#include "procedure.h"
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    initServiceQueues();
    key_t chiave = ftok(FTOK_PATH, FTOK_CHAR_RIS);
    int coda = msgget(chiave, IPC_CREAT | 0664);
    srand(time(NULL) * getpid());
    client(coda);

    exit(0);
}