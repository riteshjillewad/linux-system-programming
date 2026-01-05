#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main()
{
    char *cwd = NULL;
    int iRet = 0;
    
    cwd = getcwd(NULL, 0);
    printf("Current working directory: %s\n", cwd);
    
    iRet = chdir("./Sample");
    if(iRet == 0)
    {
        printf("Directory changed successfully\n");
    }
    else
    {
        printf("ERROR: %s\n", strerror(errno));
    }
    
    cwd = getcwd(NULL, 0);
    printf("Current working directory: %s\n", cwd);
    
    return 0;
}

