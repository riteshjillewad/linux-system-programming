#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main()
{
    pid_t pid = 0;
    
    printf("Enter the process id: \n");
    scanf("%d", &pid);
    
    kill(pid, SIGUSR1);
    
    return 0;
}

