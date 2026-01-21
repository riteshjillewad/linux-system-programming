#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handleSignal(int signum)
{
    switch(signum)
    {
        case SIGUSR1:
            printf("Received SIGUSR1 (User Defined Signal 1)\n");
            break;

        case SIGUSR2:
            printf("Received SIGUSR2 (User Defined Signal 2)\n");
            break;

        case SIGINT:
            printf("Received SIGINT (Ctrl+C / Interrupt)\n");
            break;

        case SIGTERM:
            printf("Received SIGTERM (Termination Request)\n");
            exit(0); 
            break;

        default:
            printf("Received Unknown Signal: %d\n", signum);
            break;
    }
}

int main()
{
    printf("Receiver process started...\n");
    printf("Receiver PID: %d\n", getpid());

    signal(SIGUSR1, handleSignal);
    signal(SIGUSR2, handleSignal);
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    while(1)
    {
        sleep(1);
    }

    return 0;
}

