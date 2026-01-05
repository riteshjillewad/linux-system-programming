#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#define BUFFER_SIZE 100

int main()
{
    int fd = 0;
    char buffer[BUFFER_SIZE] = {'\0'};
    int iRet = 0;
    
    /* FIRST ITERATION */
    fd = open("Demo1.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("Unable to open file!\n");
        printf("Reason: %s\n", strerror(errno));
        return -1;
    }
    printf("File opened successfully with fd: %d\n", fd);
    
    iRet = read(fd, buffer, 10);
    printf("%d bytes read successfully\n", iRet);
    printf("Data from file is: %s\n", buffer);
    close(fd);
    
    /* SECOND ITERATION */
    fd = open("Demo1.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("Unable to open file!\n");
        printf("Reason: %s\n", strerror(errno));
        return -1;
    }
    printf("File opened successfully with fd: %d\n", fd);
    
    iRet = read(fd, buffer, 10);
    printf("%d bytes read successfully\n", iRet);
    printf("Data from file is: %s\n", buffer);
    close(fd);
    
    return 0;
}
