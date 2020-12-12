#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

//max numbers of char and integers in the msg arrays
#define NUM_C 10
#define NUM_I 2

//max random integer 
#define MAX_I 9

//number of process to generate of each kind
#define NUMP_GENERATORI 3
#define NUMP_FILTRI 1
#define NUMP_CHECK 1
#define NUMP_VISUALIZZATORI 1

//key to search in the string
#define KEY_FILTRO 'x'

//msg types, each sender will give it's kind(generatore, filtro,...) type
#define GEN 1   //0 reserved to the O.S.
#define FIL 2
#define CHK 3
#define VIS 4

//Number of max iteration each process has to go through
#define MSG_TO_SEND 2
#define MSG_TO_FIL 6
#define MSG_TO_CHK 6
#define MSG_TO_VIS 6

typedef struct {
    long type;
    char stringa[NUM_C];
    int vett[NUM_I];
    int sum;
}messaggio;

//Generates a random string, NUM_I integer, sets sum to 0, and type to GEN
void generatore(int ds_msg);

//filters the msg with type == GEN, finds the char ${KEY_FILTRO}, if !found sends the msg with type = FIL
//returns -1 if there's no msg on the queue of type GEN
//returns 0 if the msg.string does not contain ${KEY_FIL}
//returns 1 if the msg.string contains ${KEY_FIL}
int filtro(int ds_msg);

//chk of the msg with type == FIL, sums the string and the int array and sets the sum field, set type = CHK
//returns -1 if there's no msg of type = FIL on the queue
//returns 0 if found
int checksum(int ds_msg);

//prints the msg with type == CHK
//returns -1 if there's no msg of type = CHK on the queue
//returns 0 if found
int visualizzatore(int ds_msg);

#endif