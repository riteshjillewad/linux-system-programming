#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main()
{
    int fd = 0;
    
    fd = open("Demo2.txt", O_RDONLY | O_CREAT, 0777);
    if(fd < 0)
    {
        printf("Unable to create file: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        printf("File created successfully with fd: %d\n", fd);
    }
    
    return 0;
}
