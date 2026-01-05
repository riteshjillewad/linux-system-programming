#include <stdio.h>
#include <unistd.h>

/* Case 3: Checking Before Removing */

int safe_remove(const char *pathname) 
{
    // Check if file exists
    if(access(pathname, F_OK) != 0) 
    {
        printf("'%s' does not exist\n", pathname);
        return -1;
    }
    
    printf("Removing '%s'...\n", pathname);
    
    if(remove(pathname) == 0) 
    {
        printf("Successfully removed '%s'\n", pathname);
        return 0;
    } 
    else 
    {
        perror("remove failed");
        return -1;
    }
}

int main() 
{
    safe_remove("temp.txt");
    printf("\n");
    safe_remove("nonexistent.txt");
    
    return 0;
}
