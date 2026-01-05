#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

int main()
{
    int fd = 0;
    
    fd = open("invalid.txt", O_RDONLY);
    if(fd == -1)
    {
        printf("Trying to open...\n");                                            // BAD! printf might change errno!
        perror("Open failed");                                                    // Might print wrong error.
    }
    else
    {
        printf("File opened successfully\n");
    }
    
    close(fd);
    return 0;
}
