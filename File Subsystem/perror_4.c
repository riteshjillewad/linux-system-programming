#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() 
{
    // 1. This fails because the file doesn't exist.
    // errno is now set to 2 (ENOENT: No such file or directory)
    int fd = open("ghost_file.txt", O_RDONLY);

    if (fd == -1) {
        // 2. THE MISTAKE: Doing a system call before perror.
        // We try to close 'fd', but fd is -1.
        // The close() system call fails and sets errno to 9 (EBADF: Bad file descriptor).
        close(fd); 

        // 3. This prints the error from step 2, NOT step 1.
        perror("Open failed");
    }

    return 0;
}
