////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:       program_1.c
// Task:       1. Accept file name from user and open it using open()
//             2. Print success message + returned file descriptor
//             3. Handle errors using perror()
// Date:       Jan 5, 2026
// Author:     Ritesh Jillewad
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define BUFFER_SIZE 50

void openFile(char *file_name)
{
    int fd = 0;
    
    printf("Opening the file...\n");
    fd = open(file_name, O_RDONLY);
    if(fd == -1)
    {
        perror("Open failed");
        return;
    }
    
    printf("%s opened successfully\n", file_name);
    printf("File descriptor allocated: %d\n", fd);
}

int main()
{
    char fileName[BUFFER_SIZE];
    
    memset(fileName, '\0', BUFFER_SIZE);
    
    printf("Enter name of file: \n");
    scanf("%[^\n]", fileName);
    
    openFile(fileName);
    
    return 0;
}
