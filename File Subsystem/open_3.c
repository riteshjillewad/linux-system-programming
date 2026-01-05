#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main()
{
    int fd = 0;
    
    /*
        Before running this file, add some content to Demo1.txt, and then run this file. Truncate commands removes the contents of the file
        and set it's length to zero, so after running this command, the contents of Demo1.txt are wipped off permanently
    */
    
    fd = open("Demo1.txt", O_WRONLY | O_TRUNC, 0777);                   
    if(fd < 0)
    {
        printf("Unable to open file: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        printf("File opened successfully with fd: %d\n", fd);
    }
    
    return 0;
}
