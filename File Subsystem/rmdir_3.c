#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

/* Case 3: Removing nested directories */

int main() 
{
    // Create nested directories
    mkdir("level1", 0755);
    mkdir("level1/level2", 0755);
    mkdir("level1/level2/level3", 0755);
    
    printf("Created nested directories:\n");
    printf("  level1/level2/level3/\n\n");
    
    // Remove from deepest to shallowest
    printf("Removing directories:\n");
    
    if(rmdir("level1/level2/level3") == 0) 
    {
        printf("  Removed: level1/level2/level3/\n");
    }
    
    if(rmdir("level1/level2") == 0) 
    {
        printf("  Removed: level1/level2/\n");
    }
    
    if(rmdir("level1") == 0) 
    {
        printf("  Removed: level1/\n");
    }
    
    printf("\nAll directories removed successfully\n");
    return 0;
}
