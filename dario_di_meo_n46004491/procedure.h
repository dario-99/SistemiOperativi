#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_


#define FTOK_PATH "./"
#define FTOK_CHAR 'd'

#define MUTEX_L 0
#define SYNCH 1

#define NUM_GENERATORI 1
#define NUM_ELABORATORI 1
#define NUM_ANALIZZATORI 2

#define MAX_SIZE 16

#define ITERAZIONI 10

//inizializzazione del buffer, e set della lunghezza ad N
void initBuffer(char* s, int* n_lett);

//Converte la stringa [a-z] in upper case
void stringToUpper(char* s);

//Genera una stringa [a-z] in lower case
void generateString(char* s, int len);

//Inverte la stringa
void invertString(char* s);

//funzioni per i processi lettore
void inizioLettura(int ds_sem, int* n_lett);
void fineLettura(int ds_sem, int* n_lett);

//funzioni per i processi scrittori
void inizioScrittura(int ds_sem);
void fineScrittura(int ds_sem);

//i 3 tipi di processi da creare
void generatore(int ds_sem, char* s, int N);
void elaboratore(int ds_sem, char* s, int* n_lett);
void analizzatore(int ds_sem, char* s, int* n_lett);

#endif