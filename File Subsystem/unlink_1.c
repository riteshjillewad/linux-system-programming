#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main()
{
    int fd = 0;
    char buffer[100];
    int iRet = 0;
    
    memset(buffer, '\0', 100);
    
    // First we create the file and write content to it
    fd = open("Unlink.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
    write(fd, "Unlink file", 11);
    printf("File created successfully\n");
    
    lseek(fd, 0, SEEK_SET);
    int n = read(fd, buffer, 11);
    printf("Data from unlink.txt is: %s\n", buffer);
    buffer[n] = '\0';
    
    // Now we unlink it
    iRet = unlink("Unlink.txt");
    if(iRet == 0)
    {
        printf("File deleted successfully\n");
    }
    else
    {
        printf("Error: %s\n", strerror(errno));
    }
    
    return 0;
}
    
