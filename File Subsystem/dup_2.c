#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main()
{
    int fd1 = 0;
    int fd2 = 0;
    char buffer[100];
    ssize_t bytes = 0;
    off_t offset = 0;

    printf("------------------------------------------\n");
    printf("FD 1\n");

    fd1 = open("file3.txt", O_RDONLY);
    if(fd1 == -1)
    {
        printf("ERROR: %s\n", strerror(errno));
        return -1;
    }

    bytes = read(fd1, buffer, 2);
    buffer[bytes] = '\0';
    printf("Read using fd1: %s\n", buffer);

    offset = lseek(fd1, 0, SEEK_CUR);
    printf("Offset after fd1 read: %ld\n", offset);

    printf("------------------------------------------\n");
    printf("Duplicating fd1 using dup()\n");

    fd2 = dup(fd1);
    if(fd2 == -1)
    {
        printf("ERROR: %s\n", strerror(errno));
        return -1;
    }

    offset = lseek(fd2, 0, SEEK_CUR);
    printf("Offset seen by fd2: %ld\n", offset);

    bytes = read(fd2, buffer, 2);
    buffer[bytes] = '\0';
    printf("Read using fd2: %s\n", buffer);

    offset = lseek(fd2, 0, SEEK_CUR);
    printf("Offset after fd2 read: %ld\n", offset);

    printf("------------------------------------------\n");

    close(fd1);
    close(fd2);
    return 0;
}

