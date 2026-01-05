#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main()
{
    int fd1 = 0;
    int fd2 = 0;
    
    fd1 = open("file1.txt", O_RDONLY);
    if(fd1 != -1)
    {
        printf("File opened successfully\n");
    }
    else 
    {
        printf("ERROR: %s\n", strerror(errno));
    }
    
    fd2 = dup2(fd1, 10);
    
    printf("Original FD: %d\n", fd1);
    printf("New FD: %d\n", fd2);
    
    close(fd1);
    close(fd2);
    
    return 0;
}

