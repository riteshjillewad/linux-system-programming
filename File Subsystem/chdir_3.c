#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>

/* Effect on file operations */

int main()
{
    char *cwd = NULL;
    int fd = 0;
    
    printf("Opening file in current directory...\n");
    fd = open("Link1.txt", O_RDONLY);
    if(fd == -1)
    {
        printf("File not found here!\n");
    }
    else
    {
        printf("File found\n");
        close(fd);
    }
    
    printf("Changing to /tmp...\n");
    chdir("/tmp");
    
    printf("Opening file in new directory..\n");
    fd = open("Link1.txt", O_RDONLY);
    if(fd == -1)
    {
        printf("File not found here!\n");
    }
    else
    {
        printf("File found\n");
        close(fd);
    }
    
    return 0;
}

