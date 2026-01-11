////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_3.c
// Task:          1. Accept directory name
//                2. Use opendir(), readdir() to print the directory names
// Date:          Jan 11, 2026
// Author:        Ritesh Jillewad
// Dependencies:  stdio.h, errno.h, string.h, sys/types.h, dirent.h
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    HEADER FILES INCLUSION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MACROS DECLERATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE 100

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         readDirectory()
// Description:  This function is used to print the directory names
// Input:        Directory name
// Output:       Directory files
// Date:         Jan 11, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void readDirectory(const char *directoryName)
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;

    /* Step 1: We need to open the directory */
    dp = opendir(directoryName);
    if(dp == NULL)
    {
        perror("Open failed");
        return;
    }
    printf("%s directory opened successfully.\n", directoryName);

    /* Step 2: We need to now read the directory contents */
    printf("Directory files: \n");
    while((ptr = readdir(dp)) != NULL)
    {
        if(strcmp(ptr -> d_name, ".") != 0 && strcmp(ptr -> d_name, "..") != 0)
        {
            printf("%s\n", ptr -> d_name);
        }
    }

    /* Step 3: We close the opened directory*/
    closedir(dp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char directoryName[BUFFER_SIZE];
    
    memset(directoryName, '\0', BUFFER_SIZE);
    
    printf("Enter name of directory: \n");
    scanf("%[^\n]", directoryName);
    
    readDirectory(directoryName);

    return 0;
}// End of main
