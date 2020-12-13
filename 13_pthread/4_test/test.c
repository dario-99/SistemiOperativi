#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "test.h"

extern int a;
void* fun(void* par){
    pthread_mutex_t *m = (pthread_mutex_t *)par;
    pthread_mutex_lock(m);
    a++;
    printf("a=%d\n", a);
    pthread_mutex_unlock(m);
}