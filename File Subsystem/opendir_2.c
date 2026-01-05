#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>

int main()
{
    /* ERROR HANDLING USING DIRENT */
    
    DIR *dp = NULL;
    
    dp = opendir("./Hello");                           // Provide non-existent directory
    if(dp == NULL)
    {
        switch(errno)
        {
            case EACCES:
                printf("Permission denied\n");
                break;
            case ENOENT:
                printf("Directory does not exists\n");
                break;
            case ENOTDIR:
                printf("Path is not a directory\n");
                break;
            case EMFILE:
                printf("Too many open files in process\n");
                break;
            case ENFILE:
                printf("Too many open files in system\n");
                break;
            default:
                printf("Error: %s\n", strerror(errno));
        }
        return 1;
    }
    
    closedir(dp);
    return 0;
}
