#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

#define MAX_BUFFER_SIZE 100

int main()
{
    int pipefd[2] = {0, 0};
    int iRet = 0;
    char buffer[MAX_BUFFER_SIZE];
    
    memset(buffer, '\0', MAX_BUFFER_SIZE);
    
    /* Now the pipe is created with the read and write ends */
    pipe(pipefd);
    
    /* Since unnamed pipes are only used between related process, so we can use the fork() system call */
    iRet = fork();
    if(iRet == 0)
    {
        printf("Child process is running...\n");
        printf("Child process is writing data to pipe.\n");
        close(pipefd[0]);
        
        write(pipefd[1], "Jay Ganesh...", 13);
        exit(0);
    }
    else
    {
        printf("Parent process is running...\n");
        printf("Parent process is reading data from pipe.\n");
        close(pipefd[1]);
        
        read(pipefd[0], buffer, 13);
        printf("Data from pipe: %s\n", buffer);
    }
    
    return 0;
}
