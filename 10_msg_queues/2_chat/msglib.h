#ifndef _MSG_LIB_H
#define _MSG_LIB_H

#define FTOK_PATH "./"
#define FTOK_CHAR 'd'

#define CLIENT_MSG 1

#define MAX_SIZE 100
#define MAX_CLIENT 20
#define ID_SERVER 1

typedef struct {
    long type;
    char msg[MAX_SIZE];
    int id; //getpid()
}msg;

void login(int ds_msqd);
//void logoff();
void sendMsg(int ds_msqd,int pid);
void recMsg(int ds_msqd,int pid);
int find(int* v, int l, int k);

#endif