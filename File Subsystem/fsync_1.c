#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/* sync(): problem with this is that it fluses all files system-wide */
/* fsync(): Syncs specific fd only */

int main()
{
    int fd1 = 0;
    int fd2 = 0;
    
    fd1 = open("Important.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    fd2 = open("LessImportant.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    
    write(fd1, "Important data", 14);
    write(fd2, "Hello", 5);
    
    printf("Syncing only important data(Important.txt)...\n");
    if(fsync(fd1) == 0)
    {
        printf("Important data synced to disk\n");
    }
    
    printf("LessImportant.txt still in the kernel buffer\n");
    
    close(fd1);
    close(fd2);
    return 0;
}
