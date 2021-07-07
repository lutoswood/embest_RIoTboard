#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define SEM_NUM      0

union semun
{
    int value;
};

static void sem_init(int sem_num,int semid)
{
    union semun sem_un;

    sem_un.value = 1;

    if(semctl(semid,sem_num,SETVAL,sem_un) == -1){
        fprintf(stderr,"Failed to init semaphore\n");
    }
}

// P操作，申请资源，信号量-1
static int sem_p(int sem_num, int semid)
{
    struct sembuf sop; 

    sop.sem_num = sem_num;
    sop.sem_op = -1; //信号量-1
    sop.sem_flg = 0; //阻塞

    if(semop(semid,&sop,1) == -1){
      fprintf(stderr,"sem_p() faild\n");
      return 0;  
    }

    return 1;
}

// V操作，释放资源，信号量+1
static int sem_v(int sem_num,int semid)
{
    struct sembuf sop; 

    sop.sem_num = sem_num;
    sop.sem_op = 1; //信号量+1
    sop.sem_flg = 0; //阻塞

    if(semop(semid,&sop,1) == -1){
      fprintf(stderr,"sem_v() faild\n");
      return 0;  
    } 

    return 1;  
}

static void sem_del(int sem_num,int semid)
{
    union semun sem_un;

    if(semctl(semid,sem_num,IPC_RMID,sem_un) == -1){
        fprintf(stderr,"Failed to delete semaphore\n");
    }
}

/*
int main(int argc, char const *argv[])
{
    pid_t pid;
    key_t key;
    int sem_id;

    key = ftok("./",123);
    if(key == -1){
        perror("ftok()");
        return -1;
    }

    sem_id = semget(key,1,IPC_CREAT|0666);
    if(sem_id == -1){
        perror("semget()");
        return -1;
    }

    sem_init(SEM_NUM,sem_id);

    pid = fork();
    if(pid > 0){
        for(int i = 0; i<10;i++){
            if(!sem_p(SEM_NUM,sem_id))
            {
                exit(EXIT_FAILURE);
            }

            //向屏幕输出字符串
            printf("parent process\n");
            fflush(stdout);

            if(!sem_v(SEM_NUM,sem_id)){
                exit(EXIT_FAILURE);
            }
            sleep(1);
        }
        sem_del(SEM_NUM,sem_id);
        wait(NULL);
        exit(EXIT_SUCCESS);

    }else if(pid == 0){
        for(int i = 0; i<10;i++){
            if(!sem_p(SEM_NUM,sem_id))
            {
                exit(EXIT_FAILURE);
            }

            //向屏幕输出字符串
            printf("child process\n");
            fflush(stdout);

            if(!sem_v(SEM_NUM,sem_id)){
                exit(EXIT_FAILURE);
            }
            sleep(1);     
        }
        exit(EXIT_SUCCESS);

    }else if(pid < 0){
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    return 0;
}
*/

int main(int argc, char const *argv[])
{
    pid_t pid;
    key_t key;
    int sem_id;

    key = ftok("./",123);
    if(key == -1){
        perror("ftok()");
        return -1;
    }

    pid = fork();
    if(pid > 0){
        for(int i = 0; i<10;i++){

            //向屏幕输出字符串
            printf("parent process\n");
            // fflush(stdout);

            sleep(1);
        }

        wait(NULL);
        exit(EXIT_SUCCESS);

    }else if(pid == 0){
        for(int i = 0; i<10;i++){
            //向屏幕输出字符串
            printf("child process\n");
            // fflush(stdout);

            sleep(1);     
        }
        exit(EXIT_SUCCESS);

    }else if(pid < 0){
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    return 0;
}
