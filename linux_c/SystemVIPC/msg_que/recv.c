#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSG_LEN     32

struct msg_buf{
    long msg_type;
    char msg_text[MSG_LEN];
};

int main(int argc,const char *argv[])
{
    key_t key;
    int msg_id;
    struct msg_buf m_buf;
    long int msgtype=0;

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
        if(msgrcv(msg_id,(void *)&m_buf,MSG_LEN,msgtype,0) == -1){
            perror("msgrcv()");
            return -1;
        }

        printf("Recv:%s\n",m_buf.msg_text);
        
        //遇到end结束
        if(strncmp(m_buf.msg_text,"end",3) == 0){
            break;
        }
    }

    //删除消息队列
    if(msgctl(msg_id,IPC_RMID,0) == -1){
        perror("msgcrl()");
        return -1;
    }

    return 0;
}