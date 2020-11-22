#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_

#define MAX_POSTI 80

#define NUM_CLIENTI 50
#define NUM_VISUALIZZATORI 1

#define MUTEX 0 
#define SEM_VETT_POSTI 1

#define LIBERO 0
#define OCCUPATO 1
#define IN_AGGIORNAMENTO 2

#define FPATH "./"
#define FCHAR 'd'

#define FPATH_VETT "./"
#define FCHAR_VETT 'c'

typedef struct {
    unsigned int id_cliente;
    unsigned int stato; 
} posto;


void visualizzatore(int sem_id, posto* vett, int* posti_disp);
void cliente(int sem_id, posto* vett, int* posti_disp);

#endif