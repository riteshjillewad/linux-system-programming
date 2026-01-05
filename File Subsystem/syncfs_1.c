#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
    int fd = 0;
    
    // Open file on specific filesystem
    fd = open("/home/ritesh-jillewad/Desktop/Ritesh_LSP/Ritesh.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    write(fd, "Data\n", 5);
    
    // Sync only the filesystem containing this file
    // (not all filesystems like sync() does)
    printf("Syncing /ritesh-jillewad filesystem only...\n");
    
    if (syncfs(fd) == 0) {
    
        printf("Filesystem synced\n");
    } else 
    {
        printf("syncfs failed");
    }
    
    close(fd);
    return 0;
}
