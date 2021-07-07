#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int i=0;

/**
 * 线程调用函数
 */
void *thread_Func(void *arg)
{
	char *str = (char *)arg;
	while(1){
		printf("%s id = %ld,i=%d\n",str,pthread_self(),i++);
		sleep(1);
		if(i == 5)
		{
			pthread_exit(NULL);
		}
	}
}

int main(int argc, const char *grav[])
{
	int err;
    pthread_t thd1;

    //make thread
    err = pthread_create(&thd1,NULL,&thread_Func,"thread1");
	if(err !=0 ){
		printf("Error:return code from pthread_create:%d\n",err);
		exit(-1);
	}

	sleep(2);

	//detach from the main thread
	err = pthread_detach(thd1);
	if(err != 0){
		perror("pthread_detach");
	}

	//由于已经分离，使用join回收会报错
	err = pthread_join(thd1,NULL);
	if(err !=0 )
	{
		printf("Error:return code from pthread_join:%d\n",err);
		exit(-1);
	}

	printf("program completed. Exiting.\n");

	return 0;
}