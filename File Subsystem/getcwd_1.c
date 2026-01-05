#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<limits.h>

int main()
{
    char path[PATH_MAX];
    
    memset(path, '\0', PATH_MAX);
    
    if(getcwd(path, PATH_MAX) != NULL)                                                    /* Standard static buffer */
    {
        printf("Current directory: %s\n", path);
    }
    else
    {
        printf("ERROR: %s\n", strerror(errno));
    }

    return 0;
}
    
