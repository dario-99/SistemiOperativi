#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

enum stati{
    VUOTO, IN_USO, PIENO
};

#define SIZE 10
#define MUTEX 0
#define MSG_DISP 1
#define SPAZIO_DISP 2


typedef struct{
    int buf[SIZE];
    int stato[SIZE];
}buff;

void produci(int ds_sem, buff *b, int val);
int consuma(int ds_sem, buff* b);

#endif