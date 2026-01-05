#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* Checking before creating files */

int main() 
{
    const char *filename = "important.txt";
    
    // Check if file already exists
    if (access(filename, F_OK) == 0) 
    {
        printf("Warning: '%s' already exists!\n", filename);
        printf("Do you want to overwrite? (y/n): ");
        
        char response;
        scanf(" %c", &response);
        
        if (response != 'y' && response != 'Y') 
        {
            printf("Operation cancelled\n");
            return 0;
        }
    }
    
    // Create or overwrite file
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) 
    {
        perror("open");
        return 1;
    }
    
    write(fd, "New content\n", 12);
    close(fd);
    
    printf("File created/updated successfully\n");
    return 0;
}
