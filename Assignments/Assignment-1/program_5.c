////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_5.c
// Task:          1. Accept file name and number of bytes N
//                2. Read exactly N bytes using read() and print on console
//                3. If file contains less than N, print only available bytes
// Date:          Jan 5, 2026
// Author:        Ritesh Jillewad
// Dependencies:  stdio.h, unistd.h, fcntl.h, errno.h, string.h, sys/stat.h, stdlib.h
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    HEADER FILES INCLUSION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MACROS DECLERATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE 50

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         readNByest
// Description:  Reads n bytes from the file
// Input:        Filename, N
// Output:       N bytes from the file
// Date:         Jan 5, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void readNBytes(const char *filename, int N)
{
    int fd = 0;
    char *buffer = NULL; 
    int bytes_read = 0;  

    // Step 1: Open the file
    fd = open(filename, O_RDONLY);
    if(fd == -1)
    {
        perror("Open failed");
        return;
    }

    // Step 2: Allocate memory dynamically for N bytes
    // We add +1 for the null terminator '\0'
    buffer = (char *)malloc(N + 1);
    
    if(buffer == NULL)
    {
        perror("Memory allocation failed");
        close(fd);
        return;
    }

    // Initialize memory to zero
    memset(buffer, 0, N + 1);

    // Step 3: Read N bytes
    bytes_read = read(fd, buffer, N);
    if(bytes_read == -1)
    {
        perror("Read failed");
    }
    else
    {
        printf("\nRequested: %d bytes | Read: %d bytes\n", N, bytes_read);
        printf("----------------------------------------\n");
        write(1, buffer, bytes_read);   
        printf("----------------------------------------\n");
    }
    // Step 4: Cleanup
    free(buffer); 
    close(fd); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char fileName[BUFFER_SIZE];
    int N = 0;

    memset(fileName, 0, BUFFER_SIZE);

    printf("Enter file name: \n");
    scanf("%[^\n]", fileName);
    getchar();
    
    printf("Enter number of bytes to read: \n");
    scanf("%d", &N);
    
    readNBytes(fileName, N);
    return 0;
}// End of main


