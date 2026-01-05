#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main()
{
    int fd1 = 0;
    int fd2 = 0;
    
    fd1 = open("file3.txt", O_RDONLY);
    if(fd1 != -1)
    {
        printf("File opened with fd: %d\n", fd1);
    }
    else 
    {
        printf("Error: %s\n", strerror(errno));
    }
    
    fd2 = dup(fd1);
    
    printf("Original file descriptor: %d\n", fd1);
    printf("Duplicate file descriptor: %d\n", fd2);
    
    close(fd1);
    close(fd2);
    return 0;
}
    
