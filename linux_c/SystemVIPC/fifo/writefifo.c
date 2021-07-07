#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#define LEN         32
#define FILE_PATH   "./fifofile"

//建立一个有名管道，进程获取控制台向管道写数据
int main (int agrc, const char *argv[])
{
    int fd;
    char buf[LEN];
    int ret;

    unlink(FILE_PATH);//取消链接,删除已存在的fifo文件

    ret = mkfifo(FILE_PATH,0666);
    if(ret == -1){
        perror("mkfifo()");
        return -1;
    }

    fd = open(FILE_PATH,O_WRONLY);
    if(fd < 0){
        perror("open()");
        return -1;
    }

    while (1){
        fgets(buf,LEN,stdin);
        write(fd,buf,LEN);
    }

    return 0;
}

