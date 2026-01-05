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
    
    /* First we need to open the file */
    fd = open("Demo1.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("Unable to open file!\n");
        printf("Reason: %s\n", strerror(errno));
        return -1;
    }
    printf("File opened successfully with fd: %d\n", fd);
    
    /* Next, we need to read the data from file */
    /* Here we read first 10 bytes of data */
    iRet = read(fd, buffer, 10);
    printf("%d bytes read successfully\n", iRet);
    printf("Data from file is: %s\n", buffer);
    
    /* Next, we need to read the data from file */
    /* Now we again read next 10 bytes of data */
    iRet = read(fd, buffer, 10);
    printf("%d bytes read successfully\n", iRet);
    printf("Data from file is: %s\n", buffer);
    
    close(fd);
    return 0;
}
