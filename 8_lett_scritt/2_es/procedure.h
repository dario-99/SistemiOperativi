#ifndef _LETT_SCRITT_H_
#define _LETT_SCRITT_H_

#define MUTEX_L 0
#define SYNCH 1
#define FTOK_PATH "./"
#define FTOK_CHAR 'd'

#define NUM_LETTORI 2
#define NUM_SCRITTORI 1

#define LETTURE 5
#define SCRITTURE 5

typedef struct{
    int val_1;
    int val_2;
    int num_lettori;
}buffer;

void inizio_lettura(int ds_sem, buffer* buf);
void fine_lettura(int ds_sem, buffer* buf);
void inizio_scrittura(int ds_sem, buffer* buf);
void fine_scrittura(int ds_sem, buffer* buf);
void lettore(int ds_sem, buffer* buf);
void scrittore(int ds_sem, buffer* buf);
#endif