#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handleSignal(int signum)
{
    printf("Signal recieved: %d\n", signum);
}

int main()
{
    int pid = 0;
    
    printf("PID of process: %d\n", getpid());
    
    signal(SIGINT, handleSignal);
    
    while(1)
    {
        sleep(1);
    }
    
    return 0;
}
