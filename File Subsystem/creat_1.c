#include<stdio.h>
#include<fcntl.h>

int main()
{
    int fd = 0;
    
    fd = creat("Demo1.txt", 0777);
    if(fd == -1)
    {
        printf("Unable to create file!\n");
        return -1;
    }
    else
    {
        printf("File created successfully with fd: %d\n", fd);
    }
    
    close(fd);
    return 0;
}
