#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main() 
{
    int fd = open("/nonexistent/directory/file.txt", O_RDONLY);
    
    if(fd == -1) 
    {
        // Method 1: Using perror
        printf("Method 1 - perror():\n");
        perror("  open failed");
        
        // Method 2: Manual (what perror does internally)
        printf("\nMethod 2 - Manual:\n");
        printf("  open failed: %s\n", strerror(errno));
        
        // Method 3: Showing errno value
        printf("\nMethod 3 - errno value:\n");
        printf("  Error code: %d (%s)\n", errno, strerror(errno));
    }
    
    return 0;
}
