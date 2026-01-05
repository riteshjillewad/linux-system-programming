#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<limits.h>

int main()
{
    char *path = NULL;
    
    path = getcwd(NULL, 0);                                                           /* Dynamic buffer */
    if(path != NULL)
    {
        printf("Current working directory: %s\n", path);
        free(path);
    }
    else
    {
        printf("ERROR: %s\n", strerror(errno));
    }
    
    return 0;
}
    
