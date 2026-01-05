#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd = 0;

    /* Open file for output */
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }

    /* Redirect stdout (fd 1) to file */
    dup2(fd, STDOUT_FILENO);

    /* Now printf goes into output.txt */
    printf("Hello from dup2 output redirection!\n");
    printf("This will be written into the file.\n");

    close(fd);
    return 0;
}

