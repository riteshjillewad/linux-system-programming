#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>

int main()
{
    DIR *dp = NULL;
    
    dp = opendir("./Data");
    if(dp == NULL)
    {
        printf("ERROR: %s\n", strerror(errno));
    }
    else
    {
        printf("Directory opened successfully!\n");
    }
    
    return 0;
}
