#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>

/* Case 2: Directory contains various files */

int main()
{
    int iRet = 0;
    
    iRet = rmdir("./Sample");
    if(iRet != 0)
    {
        printf("ERROR: %s\n", strerror(errno));
    }
    else
    {
        printf("Directory deleted successfully\n");
    }
    
    return 0;
}

