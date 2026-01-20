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
    
    /* First read operation, will read 3 bytes of data */
    read(fd, buffer, 3);
    printf("Data from named pipe is: %s\n", buffer);
    
    /* Again read operation, will read rest 10 bytes of data */
    read(fd, buffer, 10);
    printf("Data from named pipe is: %s\n", buffer);

    close(fd);    
    return 0;
}


