#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main()
{
    char *cwd = NULL;
    int iRet = 0;
    
    printf("-----------------------------------\n");
    printf("Starting directory: \n");
    cwd = getcwd(NULL, 0);
    printf("%s\n", cwd);
    
    printf("-----------------------------------\n");
    printf("Changing to /etc...\n");
    chdir("/etc");
    cwd = getcwd(NULL, 0);
    printf("Now in: %s\n", cwd);
    
    printf("-----------------------------------\n");
    printf("Changing to ..(parent)...\n");
    chdir("..");
    cwd = getcwd(NULL, 0);
    printf("Now in: %s\n", cwd);
    printf("-----------------------------------\n");
    
    return 0;
}

