#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = 0;
    char buffer[100];
    ssize_t bytesRead = 0;
    off_t offset = 0;

    fd = open("Important.txt", O_RDONLY);
    if(fd == -1)
    {
        printf("Error");
        return -1;
    }

    printf("----------------------------------------------\n");
    printf("Reading using read()...\n");

    bytesRead = read(fd, buffer, 5);
    if(bytesRead == -1)
    {
        printf("Error");
        return -1;
    }

    buffer[bytesRead] = '\0';
    printf("Data from read(): %s\n", buffer);

    offset = lseek(fd, 0, SEEK_CUR);
    printf("Current offset after read(): %ld\n", offset);

    printf("----------------------------------------------\n");
    printf("Reading using pread()...\n");

    memset(buffer, 0, sizeof(buffer));

    bytesRead = pread(fd, buffer, 5, 10);   // read 5 bytes from offset 10
    if(bytesRead == -1)
    {
        printf("Error");
        return -1;
    }

    buffer[bytesRead] = '\0';
    printf("Data from pread(): %s\n", buffer);

    offset = lseek(fd, 0, SEEK_CUR);
    printf("Current offset after pread(): %ld\n", offset);

    printf("----------------------------------------------\n");

    close(fd);
    return 0;
}

/* NOTE:
          In this code we can observe, that when we perform simple read, the file offset is set to 5 (as 5 bytes are read). 
          But when we use pread(), we stated that read 5 bytes from offset 10, so according to calculation, the current offset
          should be 5 + 10 = 15, but in reality, it's not 15, it's 5 only, so this shows that pread() does not change the file
          offset.
*/

