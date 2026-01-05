#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main()
{
    int fd = 0;
    
    fd = open("Demo1.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("Unable to open file: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        printf("File opened successfully with fd: %d\n", fd);
    }
    
    return 0;
}
