#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int fd = 0;
    int iRet = 0;
    char buffer[100];
    
    memset(buffer, '\0', 100);
    
    fd = open("Link1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    write(fd, "Ritesh", 6);
    close(fd);
    
    printf("Created Link1.txt\n");
    
    if(link("Link1.txt", "Link2.txt") == -1)
    {
        printf("Link creation failed!\n");
        return -1;
    }
    printf("Linked successfully\n");
    
    return 0;
}
