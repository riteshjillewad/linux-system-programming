#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<sys/stat.h>

int main()
{
    int iRet = 0;
    
    iRet = mkdir("./Data", 0777);
    if(iRet == 0)
    {
        printf("Directory created successfully!\n");
    }
    else
    {
        printf("Error: %s\n", strerror(errno));
    }
    
    return 0;
}
