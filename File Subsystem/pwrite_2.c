#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
    int fd = 0;
    char buffer[100];
    ssize_t ret = 0;
    off_t offset = 0;

    memset(buffer, '\0', sizeof(buffer));

    fd = open("pwrite_demo.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }

    printf("--------------------------------------------------------\n");
    printf("Writing to file using write()\n");

    write(fd, "____________________________", 28);

    offset = lseek(fd, 0, SEEK_CUR);
    printf("Offset after write(): %ld\n", offset);

    lseek(fd, 0, SEEK_SET);          
    ret = read(fd, buffer, 28);
    buffer[ret] = '\0';
    printf("Initial data: %s\n", buffer);

    printf("--------------------------------------------------------\n");
    printf("Writing to file using pwrite()\n");

    pwrite(fd, "START", 5, 0);
    pwrite(fd, "MIDDLE", 6, 11);
    pwrite(fd, "END", 3, 23);

    offset = lseek(fd, 0, SEEK_CUR);
    printf("Offset after pwrite(): %ld\n", offset);

    lseek(fd, 0, SEEK_SET);          
    memset(buffer, 0, sizeof(buffer));

    ret = read(fd, buffer, 28);
    buffer[ret] = '\0';
    printf("Modified data: %s\n", buffer);

    printf("--------------------------------------------------------\n");

    close(fd);
    return 0;
}

