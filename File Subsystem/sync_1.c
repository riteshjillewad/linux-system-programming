#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = 0;
    
    printf("Writing important data...\n");
    
    fd = open("Important.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    write(fd, "Important info", 14);
    close(fd);
    
    printf("Data written to kernel buffer\n");
    printf("Forcing sync to disk...\n");
    
    sync();
    
    printf("Sync complete - data is now on disk\n");
    printf("Safe to power off or reboot\n");
    
    return 0;
}
