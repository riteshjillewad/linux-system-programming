#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main()
{
    pid_t pid = 0;
    
    printf("PID of current process: %d\n", getpid());
    
    /* This is infinite waiting loop */
    while(1)
    {
        sleep(1);
    }
    
    return 0;
}


