#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/* Error Handling with errno */

void check_file_access(const char *filename) 
{
    printf("Checking: %s\n", filename);
    
    if(access(filename, R_OK) == -1) 
    {
        switch (errno) 
        {
            case EACCES:
                printf("  Permission denied\n");
                break;
                
            case ENOENT:
                printf("  File does not exist\n");
                break;
                
            case ENOTDIR:
                printf("  Component in path is not a directory\n");
                break;
                
            case ENAMETOOLONG:
                printf("  Path name too long\n");
                break;
                
            case EROFS:
                printf("  Read-only filesystem (checking write access)\n");
                break;
                
            default:
                printf("  Error: %s\n", strerror(errno));
        }
    } 
    else 
    {
        printf("  Access granted\n");
    }
}

int main() 
{
    check_file_access("/etc/passwd");
    check_file_access("/etc/shadow");
    check_file_access("/nonexistent/file.txt");
    
    return 0;
}
