#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>

int main()
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    int iCount = 1;
    
    dp = opendir("./Sample");
    if(dp == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        printf("Directory opened successfully!\n");
    }
    
    printf("--------------------------------------\n");
    printf("DIRECTORY CONTENTS\n");
    while((ptr = readdir(dp)) != NULL)
    {
        printf("--------------------------------------\n");
        printf("Entry number: %d\n", iCount);
        printf("File name: %s\n", ptr -> d_name);
        printf("Inode number: %ld\n", ptr -> d_ino);
        printf("File type: %d\n", ptr -> d_type);
        iCount++;
    }
    printf("--------------------------------------\n");
    
    closedir(dp);
    return 0;
}
    
