////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_4.c
// Task:          1. Accept directory name
//                2. Print each entry with it's type
//                3. Use lstat() for accurate type
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
// Name:         listFileType()
// Description:  This function is used to display the file types
// Input:        Directory name
// Output:       Directory files
// Date:         Jan 11, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void listFileType(const char *directoryName)
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
    printf("Directory contents: \n");
    while((ptr = readdir(dp)) != NULL)
    {
        if((strcmp(ptr -> d_name, ".")) != 0 && (strcmp(ptr -> d_name, "..")) != 0)
        {
            printf("File name: %s\n", ptr -> d_name);
            printf("File type: ");

            if(ptr -> d_type == DT_BLK)
            {
                printf("This is a block device\n");
            }
            else if(ptr -> d_type == DT_CHR)
            {
                printf("This is a character device.\n");
            }
            else if(ptr -> d_type == DT_DIR)
            {
                printf("This is a directory.\n");
            }
            else if(ptr -> d_type == DT_FIFO)
            {
                printf("This is named pipe(FIFO).\n");
            }
            else if(ptr -> d_type == DT_LNK)
            {
                printf("This is a symbolic link.\n");
            }
            else if(ptr -> d_type == DT_REG)
            {
                printf("This is a regular file.\n");
            }
            else if(ptr -> d_type == DT_SOCK)
            {
                printf("This is a UNIX domain socket.\n");
            }
            else if(ptr -> d_type == DT_UNKNOWN)
            {
                printf("The file type could not be determined.\n");
            }
            else
            {
                printf("Invalid input!\n");
            }
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
    
    listFileType(directoryName);

    return 0;
}// End of main
