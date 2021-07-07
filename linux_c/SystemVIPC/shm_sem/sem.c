#include "shm_sem.h"

struct sembuf sop[2];    
union semun sem_un;

void sem_init(int semid)
{
    sem_un.value = 0;
    semctl(semid,S_READ,SETVAL,sem_un);

    sem_un.value = 1;
    semctl(semid,S_WRITE,SETVAL,sem_un);
}

// P操作，申请资源，信号量-1
void p_ipc_sem(int index, int semid)
{
    sop[0].sem_num = index;
    sop[0].sem_op = -1; //信号量-1
    sop[0].sem_flg = 0; //阻塞
    semop(semid,&sop[0],1);
}

// V操作，释放资源，信号量+1
void v_ipc_sem(int index,int semid)
{
    sop[1].sem_num = index;
    sop[1].sem_op = 1; //信号量+1
    sop[1].sem_flg = 0; //阻塞
    semop(semid,&sop[1],1);
}

void sem_del(int semid)
{
    union semun sem_un;
    semctl(semid,S_READ,SETVAL,sem_un);

    semctl(semid,S_WRITE,SETVAL,sem_un);
    
}