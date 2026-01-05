/* This code will rename the files present on same directory */

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main()
{
    int fd = 0;
    
    fd = rename("./Demo1.txt", "./Rename1.txt");
    if(fd == 0)
    {
        printf("Rename successful\n");
    }
    else
    {
        printf("Unable to rename!\n");
    }
    
    return 0;
}
    
