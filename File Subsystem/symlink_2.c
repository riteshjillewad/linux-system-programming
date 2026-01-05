#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
    int fd = 0;
    char buffer[100];
    int iRet = 0;
    
    memset(buffer, '\0', 100);
    
    fd = open("Demo1.txt", O_RDONLY);
    read(fd, buffer, 20);
    printf("Data from symlink: %s\n", buffer);
    
    return 0;
}
