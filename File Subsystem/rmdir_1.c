#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>

/* Case 1: Directory is empty */

int main()
{
    int iRet = 0;
    
    iRet = rmdir("./Data");
    if(iRet == 0)
    {
        printf("Directory removed successfully\n");
    }
    else
    {
        printf("ERROR: %s\n", strerror(errno));
    }
    
    return 0;
}

