#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>

int main()
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    
    dp = opendir("./Sample");
    if(dp == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        printf("Directory opened successfully!\n");
    }
    
    /* This will give the first directory entry */
    ptr = readdir(dp);
    printf("----------------------------------\n");
    printf("First Entry: \n");
    printf("Inode number: %ld\n", ptr -> d_ino);
    printf("File name: %s\n", ptr -> d_name);
    printf("File type: %d\n", ptr -> d_type);
    
    /* This will give the second directory entry */
    ptr = readdir(dp);
    printf("----------------------------------\n");
    printf("Second Entry: \n");
    printf("Inode number: %ld\n", ptr -> d_ino);
    printf("File name: %s\n", ptr -> d_name);
    printf("File type: %d\n", ptr -> d_type);
    
    /* This will give the third directory entry */
    ptr = readdir(dp);
    printf("----------------------------------\n");
    printf("Third Entry: \n");
    printf("Inode number: %ld\n", ptr -> d_ino);
    printf("File name: %s\n", ptr -> d_name);
    printf("File type: %d\n", ptr -> d_type);
    
    /* This will give the fourth directory entry */
    ptr = readdir(dp);
    printf("----------------------------------\n");
    printf("Fourth Entry: \n");
    printf("Inode number: %ld\n", ptr -> d_ino);
    printf("File name: %s\n", ptr -> d_name);
    printf("File type: %d\n", ptr -> d_type);
    
    /* This will give the fifth directory entry */
    ptr = readdir(dp);
    printf("----------------------------------\n");
    printf("Fifth Entry: \n");
    printf("Inode number: %ld\n", ptr -> d_ino);
    printf("File name: %s\n", ptr -> d_name);
    printf("File type: %d\n", ptr -> d_type);
    
    /* This will give the sixth directory entry */
    ptr = readdir(dp);
    printf("----------------------------------\n");
    printf("Sixth Entry: \n");
    printf("Inode number: %ld\n", ptr -> d_ino);
    printf("File name: %s\n", ptr -> d_name);
    printf("File type: %d\n", ptr -> d_type);
    printf("----------------------------------\n");
    
    return 0;
}
    
