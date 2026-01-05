#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>

int main()
{
    int iRet = 0;
    
    iRet = truncate("./Sample/RenameSample.txt", 120);            // Extend the file size
    if(iRet == 0)
    {
        printf("File truncated successfully\n");
    }
    else
    {
        printf("Error: %s\n", strerror(errno));
    }
    
    return 0;
}
