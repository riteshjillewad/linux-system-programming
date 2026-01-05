#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int commit_transaction(const char *filename, const char *data) 
{
    int fd = 0;
    
    // Open transaction log
    fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
    if (fd == -1) 
    {
        printf("open failed\n");
        return -1;
    }
    
    // Write transaction data
    if (write(fd, data, strlen(data)) == -1) 
    {
        printf("write failed\n");
        close(fd);
        return -1;
    }
    
    // CRITICAL: Force to disk before acknowledging commit
    printf("Flushing transaction to disk...\n");
    if (fsync(fd) == -1) 
    {
        printf("fsync failed\n");
        close(fd);
        return -1;
    }
    
    printf("Transaction safely committed to disk\n");
    
    close(fd);
    return 0;
}

int main() 
{
    printf("Starting transaction...\n");
    
    if (commit_transaction("db.log", "TRANSACTION: INSERT user='ritesh'\n") == 0) {
    
        printf("Transaction committed successfully\n");
        printf("Safe even if system crashes now\n");
    }
    
    return 0;
}
