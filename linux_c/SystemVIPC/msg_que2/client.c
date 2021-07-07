#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSG_LEN         32
#define MSGFLAG_PARENT  1
#define MSGFLAG_CHILD   2

struct msg_buf{
    long msg_type;
    char msg_text[MSG_LEN];
};



//子进程接收终端数据并发送给服务器
//父进程接收服务器发送的数据并打印到终端
int main(int argc,const char *argv[])
{
    key_t key;
    int msg_id;
    struct msg_buf m_buf;

    key = ftok("./",123);
    if(key == -1){
        perror("ftok()");
        return -1;
    }

    msg_id = msgget(key,IPC_CREAT|0666);
    if(msg_id == -1){
        perror("msgget()");
        return -1;
    }

    while(1){
        pid_t pid;
        pid = fork();
        if(pid > 0){
            wait(NULL); //父进程等待子进程先执行
            if(msgrcv(msg_id,(void *)&m_buf,MSG_LEN,MSGFLAG_PARENT,0)  == -1){
                perror("msgrev()");
                return -1;
            }
            printf("Client Parnet RECV:%s\n",m_buf.msg_text);
        }else if (pid == 0){
            char buf[MSG_LEN];
            printf("Please enter some text:\n");
            fgets(buf,MSG_LEN,stdin);
            m_buf.msg_type = MSGFLAG_CHILD;
            strcpy(m_buf.msg_text,buf);
            if(msgsnd(msg_id,(void *)&m_buf,MSG_LEN,0) == -1){
                perror("msgsnd()");
                exit(-1);
            }

            exit(0);
        }else{
            perror("fork()");
            return 1;
        }
    }

    printf("client exit.");

    //删除消息队列
    if(msgctl(msg_id,IPC_RMID,0) == -1){
        perror("msgcrl()");
        return -1;
    }

    return 0;
}