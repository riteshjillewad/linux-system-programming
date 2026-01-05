#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
    int fd;
    char buffer[100];

    // 1. Open the file we want to read from (this must be present)
    fd = open("input_data.txt", O_RDONLY);
    
    if (fd < 0) 
    {
        printf("Failed to open input file");
        return -1;
    }

    // 2. Redirect STDIN (0) to point to our file (fd)
    // Now, when the system looks for input from FD 0, it reads the file.
    dup2(fd, STDIN_FILENO);

    // 3. Close the original fd
    close(fd);

    // 4. Use standard scanf
    // It will NOT wait for keyboard input. It reads directly from the file.
    printf("Please enter your name: "); // This still goes to screen (stdout)
    
    // scanf reads from stdin (which is now the file)
    scanf("%s", buffer); 

    printf("\nHello, %s!\n", buffer);

    return 0;
}
