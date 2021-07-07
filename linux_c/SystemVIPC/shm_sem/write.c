#include "shm_sem.h"


int main(int argc, char const *argv[])
{
    key_t key;
    int sem_id;
    int shm_id;
    char *shmaddr;

    key = ftok("./",123);
    if(key == -1){
        perror("ftok()");
        return -1;
    }

    sem_id = semget(key,2,IPC_CREAT|0666); //申请2个信号量
    if(sem_id == -1){
        perror("semget()");
        return -1;
    }

    //初始化信号量
    sem_init(sem_id);

    shm_id = shmget(key,256,IPC_CREAT|0666); //申请共享内存
    shmaddr = (char *)shmat(shm_id,NULL,0); //映射到程序的地址空间

    while (1){
        //p操作，写进程获得资源，S_WRITE信号量-1
        p_ipc_sem(S_WRITE,shm_id);

        printf("写进程，请输入：\n");
        fgets(shmaddr,32,stdin); //从终端获取数据并写入内存

        //v操作，读进程释放资源，S_READ+1
        v_ipc_sem(S_READ,shm_id);
    }
    

    return 0;
}
