#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main()
{
    int pid = 0;
    
    printf("Enter the process id: \n");
    scanf("%d", &pid);
    
    /* Send the SIGINT signal to the process id */
    kill(pid, SIGINT);
    
    return 0;
}
