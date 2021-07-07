#ifndef SHM_SEM_H
#define SHM_SEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>


#define S_READ      0
#define S_WRITE     1

union semun
{
    int value;
};


void sem_init(int semid);
void p_ipc_sem(int index, int semid);
void v_ipc_sem(int index,int semid);


#endif