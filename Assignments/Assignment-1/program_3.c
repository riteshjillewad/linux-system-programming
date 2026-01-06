////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          program_3.c
// Task:          1. Accept file name and mode(read/write/execute)
//                2. Use access to check the permission of current process
//                3. Print accessible or non-accessible with a reason
// Date:          Jan 5, 2026
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
#define BUFFER_SIZE 50

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         checkPermissions
// Description:  This function is used to check the permissions for the file
// Input:        File name and mode
// Output:       File permissions
// Date:         Jan 5, 2026
////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkPermission(const char *filename, const char *mode)
{
    int flag = 0;

    /* Step 1: Check file existence */
    if(access(filename, F_OK) != 0)
    {
        perror("File does not exist");
        return;
    }

    /* Step 2: Decide permission to check */
    if(strcmp(mode, "read") == 0)
    {
        flag = R_OK;
    }
    else if(strcmp(mode, "write") == 0)
    {
        flag = W_OK;
    }
    else if(strcmp(mode, "execute") == 0)
    {
        flag = X_OK;
    }
    else
    {
        printf("Invalid mode\n");
        return;
    }

    /* Step 3: Check permission */
    if(access(filename, flag) == 0)
    {
        printf("File is accessible for %s\n", mode);
    }
    else
    {
        perror("File is NOT accessible");
    }
}
   
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:         main
// Description:  Entry point function
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    char fileName[BUFFER_SIZE];
    char mode[10];

    memset(fileName, 0, BUFFER_SIZE);
    memset(mode, 0, sizeof(mode));

    printf("Enter file name: \n");
    scanf("%[^\n]", fileName);
    getchar();
    
    printf("Enter file mode(read/write/execute): \n");
    scanf("%[^\n]", mode);
    
    checkPermission(fileName, mode);
    
    return 0;
}// End of main


