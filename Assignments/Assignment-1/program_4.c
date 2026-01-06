////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_4.c
// Task:          1. Accept file name and display file metadata
// Date:          Jan 5, 2026
// Author:        Ritesh Jillewad
// Dependencies:  stdio.h, unistd.h, fcntl.h, errno.h, string.h, sys/stat.h
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

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MACROS DECLERATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE 50

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         checkFileType
// Description:  Helper function to check the type of file
// Input:        Mode
// Output:       File type
// Date:         Jan 5, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* checkFileType(mode_t mode)
{
    if(S_ISREG(mode))
    {
        return "Regular File";
    }
    else if(S_ISDIR(mode))
    {
        return "Directory";
    }
    else if(S_ISCHR(mode))
    {
        return "Character Device";
    }
    else if(S_ISBLK(mode))
    {
        return "Block Device";
    }
    else if(S_ISFIFO(mode))
    {
        return "FIFO";
    }
    else if(S_ISLNK(mode))
    {
        return "Symbolic Link";
    }
    else if(S_ISSOCK(mode))
    {
        return "Socket";
    }
    else
    {
        return "Unknown";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         displayFileInformation
// Description:  This function is used to display the file information
// Input:        File name and mode
// Output:       File information
// Date:         Jan 5, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayFileInformation(const char *filename)
{
    /* Pointer to stat structure (in this structure the inode fills the file metadata) */
    struct stat file_info;                                                      
    
    if(stat(filename, &file_info) == -1)
    {
        perror("stat failed");
        return;
    }
    
    printf("-----------------------------------------------\n");
    printf("|                File Metadata                |\n");
    printf("-----------------------------------------------\n");
    printf("| %-20s | %-20s |\n", "Field", "Value");
    printf("-----------------------------------------------\n");
    printf("| %-20s | %-20s |\n", "File Name", filename);
    printf("| %-20s | %-20ld |\n", "Inode Number", file_info.st_ino);
    printf("| %-20s | %-20ld |\n", "File Size (bytes)", file_info.st_size);
    printf("| %-20s | %-20ld |\n", "Links Count", file_info.st_nlink);
    printf("| %-20s | %-20d |\n", "Owner UID", file_info.st_uid);
    printf("| %-20s | %-20d |\n", "Group GID", file_info.st_gid);
    printf("| %-20s | %-20s |\n", "File Type", checkFileType(file_info.st_mode));
    printf("-----------------------------------------------\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char fileName[BUFFER_SIZE];

    memset(fileName, 0, BUFFER_SIZE);

    printf("Enter file name: \n");
    scanf("%[^\n]", fileName);
    
    displayFileInformation(fileName);
    return 0;
}// End of main


