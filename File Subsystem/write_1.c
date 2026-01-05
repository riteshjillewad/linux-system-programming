#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd = 0;
    char Buffer[] = "ABCDEFGHIJKLMNOPQRSTUVXYZ";
    int iRet = 0;
    
    fd = open("Demo2.txt", O_WRONLY);
    if(fd < 0)
    {
        printf("Unable to open file!\n");
        return -1;
    }
    else
    {
        printf("File opened with fd: %d\n", fd);
    }
    
    iRet = write(fd, Buffer, 10);
    printf("%d bytes written successfully\n", iRet);
    
    close(fd);
    return 0;
}
