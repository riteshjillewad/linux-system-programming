#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

/* Testing directory permissions */

void check_directory(const char *dirname) 
{
    printf("Checking directory: %s\n", dirname);
    
    // Check existence
    if(access(dirname, F_OK) != 0) 
    {
        printf("  Directory does not exist\n");
        return;
    }
    
    // Check if it's actually a directory
    struct stat s;
    if(stat(dirname, &s) == 0 && !S_ISDIR(s.st_mode)) 
    {
        printf("  Exists but is not a directory\n");
        return;
    }
    
    // Check read permission (can list contents)
    if(access(dirname, R_OK) == 0) 
    {
        printf("  Can list contents (read)\n");
    } 
    else 
    {
        printf("  Cannot list contents (no read)\n");
    }
    
    // Check write permission (can create/delete files)
    if(access(dirname, W_OK) == 0) 
    {
        printf("  Can create/delete files (write)\n");
    }
    else 
    {
        printf("  Cannot create/delete files (no write)\n");
    }
    
    // Check execute permission (can enter directory)
    if(access(dirname, X_OK) == 0) 
    {
        printf("  Can enter directory (execute)\n");
    } 
    else 
    {
        printf("  Cannot enter directory (no execute)\n");
    }
}

int main() 
{
    check_directory("/tmp");
    printf("\n");
    
    check_directory("/root");
    printf("\n");
    
    check_directory(".");
    
    return 0;
}
