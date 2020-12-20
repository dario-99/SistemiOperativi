#include <pthread.h>

#ifndef HEADER_H
#define HEADER_H

#define DIM_BUFFER 5

/* TBD: Definire le macro per la comunicazione su coda sincrona */

extern int coda_RTS;
extern int coda_OTS;
extern int coda_risultati;

#define FTOK_PATH_RTS "./"
#define FTOK_CHAR_RTS 'o'
#define FTOK_PATH_OTS  "./"
#define FTOK_CHAR_OTS 'p'
#define FTOK_PATH_RIS  "./"
#define FTOK_CHAR_RIS 'c'
#define MAX_SIZE 20
#define RISULTATO_TYPE 1


typedef struct {
    
    // pool di buffer condivisi
    int operandi[DIM_BUFFER];
    
    /* TBD: Aggiungere le variabili necessarie per la sincronizzazione */
    int testa;
    int coda;

    int num_msg;
    pthread_mutex_t mutex;
    pthread_cond_t spazio_disp;
    pthread_cond_t msg_disp;    //quando ci sono due msg sulla coda
    
} MonitorOperandi;

typedef struct {
    /* TBD: Definire la struttura messaggio */
    long type;
    char mess[MAX_SIZE];
} Risultato;

void inserisci_operando(MonitorOperandi * mo, int operando);
int *preleva_operando(MonitorOperandi * mo);

void inserisci_risultato(Risultato *m , int queue);
int preleva_risultato(Risultato *m, int queue, int tipomess);

void * genera_operandi(void *);
void * calcola(void *);
void preleva_risultati(int);

void initServiceQueues();
void removeServiceQueues();
    
#endif

