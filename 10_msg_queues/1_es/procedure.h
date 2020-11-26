#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define MAX_SIZE 100
#define MSG_TYPE 1

typedef struct {
    long type;
    char text[MAX_SIZE];
}msg;

void sendMsg(int ds_msg, msg m1);
void recieveMsg(int ds_msg);
#endif