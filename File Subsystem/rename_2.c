/* This code is used to move the files between the directories using rename */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main()
{
    int fd = 0;
    
    fd = rename("./Rename1.txt", "./Sample/Sample.txt");
    if(fd == 0)
    {
        printf("Files moved successfully!\n");
    }
    else
    {
        printf("Error: %s\n", strerror(errno));
    }
    return 0;
}
    
