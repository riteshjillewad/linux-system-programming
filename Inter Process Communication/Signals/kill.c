#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void handleSignal(int signum)
{
    printf("Recieved signal: %d\n", signum);
}

int main()
{
    pid_t pid;

    /* Handle the signal */
    signal(SIGINT, handleSignal);
    
    /* Find the current process id */
    pid = getpid();
    
    /* Now we generate signal using kill */
    kill(pid, SIGINT);
    
    return 0;
}
