#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int i;

/**
 * 线程调用函数
 */
 void *yellowFunc(void *arg)
 {
    char *str = (char *)arg;
    while(1){
        printf("%s thread id = %ld,i=%d \n",str,pthread_self(),i);
        i++;
        sleep(1);
    }
 }

 int main(int argc, const char *grav[])
 {
    pthread_t yellow;

    //make thread
    pthread_create(&yellow,NULL,&yellowFunc,"Yellow");
    sleep(1); //线程执行秒退出，退出后不再打印
    pthread_cancel(yellow);
    pthread_join(yellow,NULL);//回收
    printf("thread canceled \n");
    sleep(3); //线程退出5秒后进程退出
 }