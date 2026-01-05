#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main()
{
    int iRet = 0;
    char buffer[100];

    memset(buffer, '\0', sizeof(buffer));

    iRet = readlink("/home/ritesh-jillewad/Desktop/Demo1Link",
                    buffer,
                    sizeof(buffer) - 1);   // leave space for '\0'

    if(iRet == -1)
    {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }

    buffer[iRet] = '\0';   // SAFE now
    printf("The symbolic link points to: %s\n", buffer);

    return 0;
}

