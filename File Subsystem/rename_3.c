#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define BUFFER_SIZE 100

int main()
{
    int fd = 0;
    int iRet = 0;
    char buffer[BUFFER_SIZE];
    
    memset(buffer, '\0', BUFFER_SIZE);
    
    fd = open("Demo2.txt", O_RDONLY);
    if(fd != -1)
    {
        printf("File opened successfully (FD: %d)\n", fd);
    }
    else
    {
        printf("Error opening file: %s\n", strerror(errno));
        return -1; // Stop here if open failed
    }
    iRet = read(fd, buffer, BUFFER_SIZE);
    if(iRet != 0)
    {
        printf("Data from Demo2.txt is: %s\n", buffer);
    }
    
    iRet = rename("./Demo2.txt", "./Sample/RenameSampleDemo.txt");
    if(iRet == 0)
    {
        printf("File moved and renamed successfully!\n");
    }
    else
    {
        printf("Error: %s\n", strerror(errno));
    }
    iRet = read(fd, buffer, BUFFER_SIZE);
    if(iRet != 0)
    {
        printf("Data from SampleFile.txt is: %s\n", buffer);
    }
    
    return 0;
}
    
