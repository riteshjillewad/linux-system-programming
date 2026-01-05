#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
    int fd;
    char buf1[10], buf2[10];
    
    // Create file
    fd = open("compare.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
    write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
    lseek(fd, 0, SEEK_SET);  // Reset to beginning
    
    printf("--------------- Using read() ---------------\n");
    
    // Regular read - advances position
    read(fd, buf1, 5);
    buf1[5] = '\0';
    printf("First read(5): %s\n", buf1);
    printf("Position: %ld\n", lseek(fd, 0, SEEK_CUR));
    
    read(fd, buf2, 5);
    buf2[5] = '\0';
    printf("Second read(5): %s\n", buf2);
    printf("Position: %ld\n", lseek(fd, 0, SEEK_CUR));
    
    // Reset file
    close(fd);
    fd = open("compare.txt", O_RDONLY);
    
    printf("--------------- Using pread() ---------------\n");
    
    // Positional read - doesn't advance position
    pread(fd, buf1, 5, 0);
    buf1[5] = '\0';
    printf("First pread(5, offset 0): %s\n", buf1);
    printf("Position: %ld\n", lseek(fd, 0, SEEK_CUR));
    
    pread(fd, buf2, 5, 0);
    buf2[5] = '\0';
    printf("Second pread(5, offset 0): %s\n", buf2);
    printf("Position: %ld\n", lseek(fd, 0, SEEK_CUR));
    
    close(fd);
    return 0;
}

