#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd = 0;
    off_t offset = 0;
    
    fd = open("demo.txt", O_WRONLY | O_CREAT, 0777);

    pwrite(fd, "HELLO", 5, 10);   // write at offset 10

    offset = lseek(fd, 0, SEEK_CUR);
    printf("Current offset: %ld\n", offset);

    close(fd);
    return 0;
}

