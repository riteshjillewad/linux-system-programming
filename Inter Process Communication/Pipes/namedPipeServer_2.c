/* THIS IS THE SERVER CODE -> THIS CODE WILL WRITE DATA TO NAMED PIPE */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
    int fd = 0;
    int iRet = 0;
    
    iRet = mkfifo("/tmp/myPipe", 0666);
    if(iRet == -1)
    {
        perror("Unable to create named pipe");
        return -1;
    }
    
    /* Since named pipes are treated as special files internally, so we can use open(), read(), write() calls */
    fd = open("/tmp/myPipe", O_WRONLY);
    if(fd == -1)
    {
        perror("Unable to open named pipe");
        return -1;
    }
    
    /* Now the pipe is opened, and we will write the data into pipe */
    write(fd, "Jay Ganesh...", 13);
    
    close(fd);
    unlink("/tmp/myPipe");        /* We need to remove the pipe, as the pipe which is created is for one client only, it cannot be reused */
    
    return 0;
}


