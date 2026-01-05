#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
    int fd = 0;
    char buffer[100];
    int iRet = 0;
    
    memset(buffer, '\0', 100);
    
    fd = open("Symlink.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
    write(fd, "Symbolic link", 13);
    close(fd);
    
    printf("Symlink.txt created successfully\n");
    
    iRet = symlink("Symlink.txt", "Demo1.txt");
    if(iRet == 0)
    {
        printf("Symlink created successfully\n");
    }
    else
    {
        printf("%s\n", strerror(errno));
    }
    
    return 0;
}
