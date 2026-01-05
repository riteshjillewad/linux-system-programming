#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd = 0;
    char buffer[100] = {'\0'};
    int iRet = 0;
    
    fd = open("Demo1.txt", O_RDWR);
    if(fd < 0)
    {
        printf("Unable to open file!\n");
        return -1;
    }
    else
    {
        printf("File opened with fd: %d\n", fd);
    }
    
    int current_pos = lseek(fd, 0, SEEL_CURR);
    printf("Current offset(cursor) position: %d\n", current_pos);
    
    return 0;
}
