#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
    int fd = 0;
    int ret = 0;
    
    fd = open("Link1.txt", O_WRONLY);
    if(fd == -1) 
    {
        printf("Open failed: %s\n", strerror(errno));
        return -1;
    }
    
    ret = ftruncate(fd, 100); 
    if(ret == 0) 
    {
        printf("Truncate successful! File is now 100 bytes.\n");
    } 
    else 
    {
        printf("Truncate failed: %s\n", strerror(errno));
    }
    
    close(fd);
    return 0;
}
