#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int i;

/**
 * 线程调用函数
 */
void *thread_Func1(void *arg)
{
	sleep(1);
    printf("thread_Func1 returning\n");
    return((void*)1);
}

 /**
 * 线程调用函数
 */
void *thread_Func2(void *arg)
{
	sleep(1);
    printf("thread_Func2 returning\n");
    pthread_exit((void*)2);
}

int main(int argc, const char *grav[])
{
	int err;
    pthread_t thd1,thd2;
	void *tret;

    //make thread
    err = pthread_create(&thd1,NULL,&thread_Func1,"thread1");
	if(err !=0 ){
		printf("Error:return code from pthread_create:%d\n",err);
		exit(-1);
	}

	pthread_create(&thd2,NULL,&thread_Func2,"thread2");
		if(err !=0 ){
		printf("Error:return code from pthread_create:%d\n",err);
		exit(-1);
	}

	err = pthread_join(thd1,&tret);
	if(err !=0 )
	{
		printf("Error:return code from pthread_join:%d\n",err);
		exit(-1);
	}
	printf("thread_Func1 exit code:%ld\n",(long)(tret));

	err = pthread_join(thd2,&tret);
	if(err !=0 )
	{
		printf("Error:return code from pthread_join:%d\n",err);
		exit(-1);
	}
	printf("thread_Func2 exit code:%ld\n",(long)(tret));

	printf("program completed. Exiting.\n");
}