#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>

int main()
{
    DIR *dp = NULL;
    int iRet = 0;
    
    dp = opendir("./Sample");
    if(dp == NULL)
    {
        printf("ERROR: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        printf("Directory opened successfully!\n");
    }
    
    iRet = closedir(dp);
    if(iRet == 0)
    {
        printf("Directory closed successfully!\n");
    }
    else
    {
        printf("ERROR: %s\n", strerror(errno));
    }
    
    return 0;
}
    
