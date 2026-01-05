#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/* sync(): problem with this is that it fluses all files system-wide */

int main()
{
    int fd1 = 0;
    int fd2 = 0;
    int fd3 = 0;
    
    fd1 = open("file1.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    fd2 = open("file2.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    fd3 = open("file3.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    
    write(fd1, "file1 data", 10);
    write(fd2, "file2 data", 10);
    write(fd3, "file3 data", 10);
    
    printf("Data written to 3 files\n");
        
    printf("Calling sync() - flushes ALL pending writes\n");
    sync();
    
    printf("All data written to disk\n");
    
    close(fd1);
    close(fd2);
    close(fd3);
    
    return 0;
}
