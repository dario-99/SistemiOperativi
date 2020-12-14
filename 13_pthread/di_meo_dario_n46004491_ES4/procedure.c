#include "header.h"



void inizializza(struct monitor* m){

	m->molo=0;
	m->id_nave=0;

    /* TBD: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */
    pthread_cond_init(&(m->ok_lett), NULL);
    pthread_cond_init(&(m->ok_scritt), NULL);
    pthread_mutex_init(&(m->mutex), NULL);
    m->num_scrittori = 0;
    m->num_lettori = 0;
    m->scrittori_on_cond = 0;

}

void rimuovi (struct monitor* m){
    /* TBD: Disattivare mutex e variabili condition */
    pthread_mutex_destroy(&(m->mutex));
    pthread_cond_destroy(&(m->ok_scritt));
    pthread_cond_destroy(&(m->ok_lett));
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_molo(struct monitor* m, int molo){

    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della SCRITTURA
     */
    pthread_mutex_lock(&(m->mutex));
    while(m->num_lettori > 0 || m->num_scrittori > 0){
        m->scrittori_on_cond++;
        pthread_cond_wait(&(m->ok_scritt), &(m->mutex));
        m->scrittori_on_cond--;
    }
    m->num_scrittori++;
    pthread_mutex_unlock(&(m->mutex));

    m->molo = molo;

    pthread_mutex_lock(&(m->mutex));
    m->num_scrittori--;
    if(m->scrittori_on_cond > 0){
        pthread_cond_signal(&(m->ok_scritt));
    }
    else{
        pthread_cond_broadcast(&(m->ok_lett));
    }
    pthread_mutex_unlock(&(m->mutex));
}


//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_molo(struct monitor* m){

    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della LETTURA
     */
    pthread_mutex_lock(&(m->mutex));
    while(m->num_scrittori > 0){
        pthread_cond_wait(&(m->ok_lett), &(m->mutex));
    }
    m->num_lettori++;
    pthread_mutex_unlock(&(m->mutex));

    int pos = m->molo;

    pthread_mutex_lock(&(m->mutex));
    m->num_lettori--;
    if(m->num_lettori == 0){
        pthread_cond_signal(&(m->ok_scritt));
    }
    pthread_mutex_unlock(&(m->mutex));
    return pos;
}

