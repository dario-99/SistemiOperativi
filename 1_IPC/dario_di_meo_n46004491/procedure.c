#include "semafori.h"
#include "procedure.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//inizializzazione del buffer
void initBuffer(char *s, int* n_lett){
    strcpy(s, "");  //cosi' sono sicuro che ho inserito il \0
    *n_lett = 0;
}

//Genera una stringa [a-z] in lower case
void generateString(char* s, int len){
    srand(time(NULL) * getpid());
    int i;
    for(i = 0; i < len; i++){
        s[i] = 'a' + (rand()%26);
    }
    s[len] = '\0';
}

//Converte la stringa [a-z] in upper case
void stringToUpper(char* s){
    int i = 0;
    while(s[i] != '\0'){
        if(s[i]<='z' && s[i] >= 'a'){
            s[i] -= 32;
        }
        i++;
    }
}

//Inverte la stringa s
void invertString(char* s){
    //calcolo len
    int len = strlen(s);
    int i;
    char temp;
    for(i = 0; i<len/2; i++){
        temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

//funzioni per i processi lettore
void inizioLettura(int ds_sem, int* n_lett){
    Wait_Sem(ds_sem, MUTEX_L);
    *n_lett = *n_lett + 1;
    if((*n_lett) == 1){
        Wait_Sem(ds_sem, SYNCH);
    }
    Signal_Sem(ds_sem, MUTEX_L);
}
void fineLettura(int ds_sem, int* n_lett){
    Wait_Sem(ds_sem, MUTEX_L);
    *n_lett = *n_lett - 1;
    if((*n_lett) == 0)
        Signal_Sem(ds_sem, SYNCH);
    Signal_Sem(ds_sem, MUTEX_L);
}

//funzioni per i processi scrittori, con STARVATION
void inizioScrittura(int ds_sem){
    Wait_Sem(ds_sem, SYNCH);
}
void fineScrittura(int ds_sem){
    Signal_Sem(ds_sem, SYNCH);
}

//i 3 tipi di processi da creare
//[SCRITTORE] genera una stringa casuale dato in input N la lunghezza, su una stringa condivisa rispettando i vincoli del problema lettori scrittori
void generatore(int ds_sem, char* s, int N){
    inizioScrittura(ds_sem);
    sleep(1);
    generateString(s, N);
    printf("[GENERATORE %d]: %s\n", getpid(), s);
    fineScrittura(ds_sem);
}

//[LETTORE] Rende in Uppercase la stringa in memoria condivisa, rispettando i vincoli del problema lettori scrittori
void elaboratore(int ds_sem, char* s, int* n_lett){
    char buff[MAX_SIZE];
    inizioLettura(ds_sem, n_lett);
    strcpy(buff, s);
    stringToUpper(buff);
    printf("\t[ELABORATORE %d]: %s\n", getpid(), buff);
    fineLettura(ds_sem, n_lett);
}

//[LETTORE] Inverte la stringa allocata in memoria condivisa rispettando i vincoli del problema lettori scrittori 
void analizzatore(int ds_sem, char* s, int* n_lett){
    char buff[MAX_SIZE];
    inizioLettura(ds_sem, n_lett);
    strcpy(buff, s);
    invertString(buff);
    printf("\t\t[ANALIZZATORE %d]: %s\n", getpid(), buff);
    fineLettura(ds_sem,n_lett);
}