#include <pthread.h>
typedef long msg;

struct ProdCons{
    msg mess;

    int ok_produzione;
    int ok_consumo;

    pthread_mutex_t mutex;
    pthread_cond_t ok_prod_cv;
    pthread_cond_t ok_cons_cv;
};
void Produci(struct ProdCons *pc, msg m);
void Consuma(struct ProdCons *pc, msg m);
void* consumatore(void*);
void* produttore(void*);