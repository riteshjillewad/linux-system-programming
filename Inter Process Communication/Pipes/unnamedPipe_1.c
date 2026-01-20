#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define MAX_BUFFER_SIZE 100

int main()
{
    int pipefd[2] = {0, 0};
    int iRet = 0;
    char buffer[MAX_BUFFER_SIZE];
    
    memset(buffer, '\0', MAX_BUFFER_SIZE);
    
    iRet = pipe(pipefd);
    if(iRet != 0)
    {
        perror("Unable to create unnamed pipe!\n");
        return -1;
    }
    
    /* We will write data to write end of pipe */
    write(pipefd[1], "Jay ganesh...", 13);
    
    /* We will read data from read end of pipe */
    read(pipefd[0], buffer, 13);
    printf("Data from unnamed pipe is: %s\n", buffer);
    
    return 0;
}
