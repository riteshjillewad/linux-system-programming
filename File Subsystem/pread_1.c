#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd = 0;
    char buffer[100];
    int iRet = 0;
    
    fd = open("Important.txt", O_RDONLY);
    
    pread(fd, buffer, 5, 0);                                 /* Read 5 bytes from offset 0 */
    buffer[5] = '\0';
    printf("Data from pread: %s\n", buffer);
    
    iRet = lseek(fd, 0, SEEK_CUR);
    printf("Current offset: %d\n", iRet);
    
    close(fd);
    return 0;
}
    
