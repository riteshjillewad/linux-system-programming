#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

/* Case 1: Removing the files */
int main()
{
    int fd = 0;
    int iRet = 0;
    
    iRet = remove("output.txt");
    if(iRet == 0)
    {
        printf("Successfully removed: output.txt\n");
    }
    else
    {
        printf("Remove failed\n");
        return -1;
    }
    
    fd = open("output.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("Open failed");
    }
    
    return 0;
}
        
