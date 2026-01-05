#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/* sync():      problem with this is that it fluses all files system-wide */
/* fsync():     syncs specific fd only */
/* fdatasync(): syncs only the data for the specifc fd, not metadata */

int main()
{

    int fd = 0;
    
    fd = open("Rambo.txt", O_WRONLY | O_CREAT, 0777);
    write(fd, "Hello", 5);
    
    printf("Syncing data only (not metadata)...\n");
    fdatasync(fd);
    
    printf("Data is on disk, meta-data might not be on disk\n");

    close(fd);
    return 0;
}
