/* THIS IS MESSAGE QUEUE CLIENT CODE -> IT WILL READ DATA FROM MESSAGE QUEUE */

#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>

#define MAX_BUFFER_SIZE 512

struct riteshMessage
{
    long int msgtype;
    char buffer[MAX_BUFFER_SIZE];
};

int main()
{
    key_t key;
    int mqid = 0;
    int iRet = 0;
    struct riteshMessage robj;
    
    key = ftok(".", 'r');
    if(key == -1)
    {
        printf("Unable to create unique key!\n");
        return -1;
    }
    
    mqid = msgget(key, 0666);
    if(mqid == -1)
    {
        printf("Unable to create message queue by client!\n");
        return -1;
    }
    
    iRet = msgrcv(mqid, (void *)&robj, MAX_BUFFER_SIZE, 11, 0);
    if(iRet > 0)
    {
        printf("Message read successfully from message queue by client.\n");
        printf("Message: %s\n", robj.buffer);
    }
    
    return 0;
}

