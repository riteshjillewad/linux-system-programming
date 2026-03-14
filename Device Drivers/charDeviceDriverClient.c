/* This is the client code that will interact with the character device driver */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define DEVICE_PATH "/dev/char_driver"

int main()
{
    int fd = 0;
    int ret = 0;

    char readBuffer[MAX_BUFFER_SIZE];
    char writeBuffer[MAX_BUFFER_SIZE];

    memset(readBuffer, '\0', sizeof(readBuffer));
    memset(writeBuffer, '\0', sizeof(writeBuffer));

    printf("Opening the device....\n");

    fd = open(DEVICE_PATH, O_RDWR);

    if (fd == -1)
    {
        printf("ERROR: Unable to open the device!\n");
        return -1;
    }

    printf("Device opened successfully\n");

    printf("Enter data to send:\n");

    fgets(writeBuffer, MAX_BUFFER_SIZE, stdin);

    // Finds the index of newline and replaces it with the null terminator
    writeBuffer[strcspn(writeBuffer, "\n")] = 0;

    printf("Writing data to device....\n");

    // echo "Jay ganesh" > /dev/char_driver
    ret = write(fd, writeBuffer, strlen(writeBuffer));

    if (ret < 0)
    {
        printf("ERROR: Unable to write to device!\n");
        close(fd);
        return -1;
    }

    printf("Data successfully written to device\n");

    printf("Reading data from device...\n");

    // cat /dev/char_driver
    ret = read(fd, readBuffer, MAX_BUFFER_SIZE);

    if (ret < 0)
    {
        printf("ERROR: Unable to read from device!\n");
        close(fd);
        return -1;
    }

    readBuffer[ret] = '\0';

    printf("Data received: %s\n", readBuffer);

    printf("Closing the device...\n");
    close(fd);

    return 0;
}
