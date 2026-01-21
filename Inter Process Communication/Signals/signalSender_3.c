#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main()
{
    int pid = 0;
    int choice = 0;
    int sig = 0;

    printf("Enter Receiver PID: \n");
    scanf("%d", &pid);

    printf("Choose Signal to Send:\n");
    printf("1 -> SIGUSR1\n");
    printf("2 -> SIGUSR2\n");
    printf("3 -> SIGINT\n");
    printf("4 -> SIGTERM\n");
    
    printf("Enter choice: \n ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            sig = SIGUSR1;
            break;

        case 2:
            sig = SIGUSR2;
            break;

        case 3:
            sig = SIGINT;
            break;

        case 4:
            sig = SIGTERM;
            break;

        default:
            printf("Invalid choice!\n");
            return -1;
    }

    if(kill(pid, sig) == -1)
    {
        perror("kill failed");
        return -1;
    }

    printf("Signal sent successfully to PID %d\n", pid);
    return 0;
}

