#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSG_LEN     32

struct msg_buf{
    long msg_type;
    char msg_text[MSG_LEN];
};

int main(int argc, const char *argv[])
{
    key_t key;
    int msg_id;
    struct msg_buf m_buf;
    char buffer[MSG_LEN];

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
        printf("Please enter some text: \n");
        fgets(buffer,MSG_LEN,stdin);
        m_buf.msg_type = 1;
        strcpy(m_buf.msg_text,buffer);

        //向队列中发送数据
        if(msgsnd(msg_id,(void *)&m_buf,MSG_LEN,0) == -1){
            // fprintf(stderr,"msgsnd failed\n");
            // exit(EXIT_FAILURE);
            perror("msgsed()");
            return -1;
        }
        
        //输入 end 结束
        if(strncmp(buffer,"end",3) == 0){
            break;
        }

        sleep(1);
    }

    

    return 0;
    // exit(EXIT_SUCCESS);
}