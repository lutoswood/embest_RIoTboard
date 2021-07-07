#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define LEN         32
#define FILE_PATH   "./fifofile"

//打开一个fifo文件，从管道中读取数据并打印到终端
int main(int argc, const char *argv[])
{
    int fd;
    char buf[LEN];
    size_t size;

    fd = open(FILE_PATH,O_RDONLY);//打开管道文件
    if(fd < 0){
        perror("open()");
        return -1;
    }   

    while(1){
        memset(buf,0,LEN);
        size = read(fd,buf,LEN);//读取管道数据
        if(size > 0 ){
            printf("Read:%s\n",buf);
        }
    }

    return 0 ;
}
