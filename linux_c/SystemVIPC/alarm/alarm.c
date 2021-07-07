#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int count = 0;

void timeOut(int signal)
{

    printf("alarm time out:%d\n",++count);
    alarm(1);
}

int main(int argc,const char *argv[])
{
    alarm(1);
    signal(SIGALRM,timeOut);
    while(1);

    return 0;
}