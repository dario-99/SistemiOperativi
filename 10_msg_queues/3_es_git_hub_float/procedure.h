#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define FTOK_PATH "./"
#define FTOK_CHAR 'd'

//Number of msg to send to p3
#define MSG_TO_SEND 11
#define DEBUG_M
//float interval
#define i_sx 0
#define i_dx 10

typedef struct{
    long type;
    int PROCESS_ID;
    float FLOAT_VALUE;
}msg;


//asynchronous send on the msg queue
int send_msg(int ds_msg, msg* m);

//read a msg from the msgqueue
int receive_msg(int ds_msg, msg* m);

//generate a random float given the interval, returns -1 in case of invalid interval
int rand_float(float x1, float x2, float *res);

//generate a msg given the pid=[1,2] and a float, returns -1 in case invalid pid
int generate_msg(int pid, msg* m);


#endif