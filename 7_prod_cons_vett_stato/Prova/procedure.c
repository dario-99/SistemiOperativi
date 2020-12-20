#include "procedure.h"
#include "semafori.h"
#include <unistd.h>
#include <stdio.h>
void produci(int ds_sem, buff *b, int val){
    Wait_Sem(ds_sem, SPAZIO_DISP);
    Wait_Sem(ds_sem, MUTEX);
    int i=0;
    while (i<SIZE && b->stato[i] != VUOTO)
    {
        i++;
    }
    b->stato[i] = IN_USO;
    Signal_Sem(ds_sem, MUTEX);

    sleep(2);
    b->buf[i] = val;
    b->stato[i] = PIENO;
    Signal_Sem(ds_sem, MSG_DISP);
}
int consuma(int ds_sem, buff* b){
    printf("entro in consuma\n");
    Wait_Sem(ds_sem, MSG_DISP);
    printf("Consumatore entro in MSG_DISP\n");
    Wait_Sem(ds_sem, MUTEX);
    printf("Consumatore entro nel mutex\n");
    int i=0;
    int val;
    while(i<SIZE && b->stato[i] != PIENO){
        i++;
    }
    b->stato[i] = IN_USO;
    Signal_Sem(ds_sem, MUTEX);

    sleep(2);
    b->stato[i] = VUOTO;
    val = b->buf[i];
    Signal_Sem(ds_sem, SPAZIO_DISP);
    return val;
}