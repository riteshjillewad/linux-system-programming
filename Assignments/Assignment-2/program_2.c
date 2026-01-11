////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_1.c
// Task:          1. Accept file name and string from user
//                2. Write string using write()(append mode by default)
//                3. Show total bytes read
// Date:          Jan 11, 2026
// Author:        Ritesh Jillewad
// Dependencies:  stdio.h, unistd.h, fcntl.h, errno.h, string.h
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    HEADER FILES INCLUSION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MACROS DECLERATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE 100

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         writeFile
// Description:  This function is used to write the contents to file
// Input:        File name, string
// Output:       File contents
// Date:         Jan 11, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void writeFile(const char *fileName, char string[])
{
    int fd = 0;
    char buffer[BUFFER_SIZE];
    int iRet = 0;

    memset(buffer, '\0', BUFFER_SIZE);

    /* Step 1: We first need to open the file */
    fd = open(fileName, O_CREAT | O_RDWR | O_APPEND, 0777);
    if(fd == -1)
    {
        perror("Open failed");
        return;
    }
    
    /* Step 2: Now we need to write the contents to the file */
    iRet = write(fd, string, strlen(string));
    if(iRet == -1) 
    {
        perror("Write failed");
        close(fd);
        return;
    }
    printf("%d bytes written to %s successfully\n", iRet, fileName);

    /* Step 3: Move the file offset back to the beginning to read (due to append it will be at last byte due to write) */
    lseek(fd, 0, SEEK_SET);

    /* Step 4: Now we can read the file contents from the start */
    printf("Current file content: \n");
    int totalRead = 0;
    while((iRet = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        write(1, buffer, iRet);
        totalRead += iRet;
    }
    printf("\nTotal file size: %d bytes\n", totalRead);

    close(fd);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char fileName[BUFFER_SIZE];
    char string[BUFFER_SIZE];
    
    memset(fileName, '\0', BUFFER_SIZE);
    memset(fileName, '\0', BUFFER_SIZE);
    
    printf("Enter name of file: \n");
    scanf("%[^\n]", fileName);
    getchar();

    printf("Enter file content: \n");
    scanf("%[^\n]", string);
    
    writeFile(fileName, string);
    
    return 0;
}// End of main
