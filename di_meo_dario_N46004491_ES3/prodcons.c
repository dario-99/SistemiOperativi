#include <stdio.h>
#include <unistd.h>

#include "prodcons.h"

void inizializza(ProdCons * p) {

    /* TBD: Inizializzazione del monitor */
    p->testa = 0;
    p->coda = 0;
    p->totale_elementi = 0;
    init_monitor(&(p->m), 2);
}

void consuma(ProdCons * p) {

    /* TBD: Ingresso nel monitor */
    enter_monitor(&(p->m));

    printf("[%d] Ingresso consumatore\n", getpid());

    /* TBD: Sospendere qui il consumatore se non ci sono
     *      *almeno* 3 elementi disponibili nel vettore
     */
    if(p->totale_elementi < 3){
        wait_condition(&(p->m), MSG_3DISP);
    }
    int i;
    for(i=0; i<N_CONSUMA; i++){
        printf("\t[%d] Consumo: %ld\n", getpid(), p->vettore[p->coda]);
        p->coda = (p->coda+1)%DIM;
        p->totale_elementi--;
    }
    /* TBD: Effettuare signal_condition() per svegliare i produttori
     *      in accordo al numero di elementi consumati
     */
    for(i=0; i<N_CONSUMA; i++){
        signal_condition(&(p->m), SPAZIO_DISP);
    }

    printf("[%d] Uscita consumatore\n", getpid());

    /* TBD: Uscita dal monitor */
    leave_monitor(&(p->m));
}

void produci(ProdCons * p, int val) {

    /* TBD: Ingresso nel monitor */
    enter_monitor(&(p->m));
    printf("[%d] Ingresso produttore\n", getpid());

    /* TBD: Sospendere qui il produttore se il vettore è già pieno */
    if(p->totale_elementi == DIM){
        wait_condition(&(p->m), SPAZIO_DISP);
    }

    p->vettore[p->testa] = val;
    p->testa = (p->testa + 1) % DIM;
    p->totale_elementi++;

    printf("[%d] Produzione: val=%d\n", getpid(), val);

    
    /* TBD: Svegliare un consumatore *solo se* sono disponibili almeno 3 messaggi. 
     *      Poiché è richiesto di utilizzare la semantica di Hoare, il consumatore
     *      sarà attivato immediatamente al momento della signal_condition().
     */
    if(p->totale_elementi >= 3){
        signal_condition(&(p->m), MSG_3DISP);
    }
    printf("[%d] Uscita produttore\n", getpid());

    /* TBD: Uscita dal monitor */
    leave_monitor(&(p->m));
}

void rimuovi(ProdCons * p) {

    /* TBD: Deallocazione del sotto-oggetto monitor */
    remove_monitor(&(p->m));
}
