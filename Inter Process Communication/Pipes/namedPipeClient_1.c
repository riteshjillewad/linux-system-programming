/* THIS IS THE CLIENT CODE -> THIS CODE WILL READ DATA FROM NAMED PIPE */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

#define MAX_BUFFER_SIZE 100

int main()
{
    int fd = 0;
    int iRet = 0;
    char buffer[MAX_BUFFER_SIZE];
    
    fd = open("/tmp/myPipe", O_RDONLY);
    if(fd == -1)
    {
        perror("Unable to open named pipe");
        return -1;
    }
    
    read(fd, buffer, 13);
    printf("Data from named pipe is: %s\n", buffer);
    
    close(fd);
    return 0;
}


