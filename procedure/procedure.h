#ifndef _PROCEDURE_H
#define _PROCEDURE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int wait_sem(int id_sem, int num_sem);
int signal_sem(int id_sem, int num_sem);

#endif