#include <stdio.h>
#include <sys/stat.h>

/* Case 2: Removing an empty directory */

int main() 
{
    if(mkdir("testdir", 0755) == 0) 
    {
        printf("Created: testdir/\n");
    }
    
    if(remove("testdir") == 0) 
    {
        printf("Successfully removed: testdir/\n");
    } 
    else 
    {
        perror("remove failed");
        return 1;
    }
    
    return 0;
}
