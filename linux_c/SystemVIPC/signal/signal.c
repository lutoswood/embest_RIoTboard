#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int count=0;

void signal_handler(int signal)
{
    printf("window changed %d!\n",count);
    if(signal == SIGWINCH){
        count++;
    }

    if(count == 3){
        raise(SIGKILL); //改变三次，结束本进程
        // kill(getpid(),SIGKILL);
    }
}

int main(int argc,const char *argv[])
{
    signal(SIGWINCH,signal_handler);//信号SIGWINCH发生后执行winhandle函数
    while (1){
        sleep(5);
    }
    
    return 0;
}