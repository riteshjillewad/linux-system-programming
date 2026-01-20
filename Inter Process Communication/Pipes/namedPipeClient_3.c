/* THIS IS THE CLIENT CODE -> THIS CODE WILL READ DATA FROM NAMED PIPE */

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>


#define MAX_BUFFER_SIZE 100

int main()
{

    int fd = 0;
    int iRet = 0; 
    char buffer[MAX_BUFFER_SIZE];  
    
    memset(buffer, '\0', MAX_BUFFER_SIZE);

    /* Opening the pipe */
    fd = open("/tmp/myPipe", O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open named pipe!\n");
        return -1;
    }

    /* Reading the data from pipe */
    read(fd, Arr, 3);                                       
    printf("Data gets successfully read from the pipe by client\n");
    printf("Data from pipe: %s\n", Arr);
    close(fd);                                                              /* Will close jay wala part */
    /* Due to client close, the server thinks client is gone, so there server goes and deletes the prev pipe */

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /* This will not print as due to above close, the server thinks reading is done, so it closes */

    fd = open("/tmp/myPipe", O_RDONLY);
    if(fd == -1)
    {
        printf("Unable to open named pipe!\n");
        return -1;
    }

    /* Again reading data from pipe */
    read(fd, Arr, 7);                                       
    printf("Data gets successfully read from the pipe by client\n");
    printf("Data from pipe: %s\n", Arr);

    close(fd);
    return 0;
}
