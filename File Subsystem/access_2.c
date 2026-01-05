#include <stdio.h>
#include <unistd.h>

void check_file_permission(const char *filename)
{
    // Check if file exists
    if(access(filename, F_OK) == 0)
    {
        printf("%s exists\n", filename);
    } 
    else 
    {
        printf("%s does not exist\n", filename);
        return;
    }
    
    // Check read permission
    if(access(filename, R_OK) == 0) 
    {
        printf("%s is readable\n", filename);
    } 
    else 
    {
        printf("%s is NOT readable\n", filename);
    }
    
    // Check write permission
    if(access(filename, W_OK) == 0) 
    {
        printf("%s is writable\n", filename);
    } 
    else 
    {
        printf("%s is NOT writable\n", filename);
    }
    
    // Check execute permission
    if(access(filename, X_OK) == 0) 
    {
        printf("%s is executable\n", filename);
    } 
    else 
    {
        printf("%s is NOT executable\n", filename);
    }
}

int main()
{
    char filename[256];

    printf("Enter file name: \n");
    scanf("%255[^\n]", filename);

    check_file_permission(filename);
    return 0;
}
