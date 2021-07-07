#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 32


// 建立一个无名管道，父进程从终端获取数据写入管道，子进程从管道读取数据并打印到终端
int main(int agrc,const char *argv[])
{
    int ret;
    int fd[2];
    pid_t pid;
    char buf[LEN];

    //创建无名管道
    ret = pipe(fd);
    if(ret != 0){
        perror("pipe()");
        return -1;
    }

    pid = fork();
    if(pid < 0){
        perror("fork()");
        return -1;
    }else if(pid == 0 ){ //child process
        while(1){
            memset(buf,0,LEN);
            ret = read(fd[0],buf,LEN);//从管道读
            if(ret < 0 )
                continue;
            printf("fd[0]:%s\n",buf);
        }
    }else{  //paraent process
        char str[LEN];
        while(1){
            fgets(str,LEN,stdin);
            ret = write(fd[1],str,LEN);
            if(ret == -1){
                perror("write()");
            }
        }
    }

    return 0;

}