/* THIS IS MESSAGE QUEUE SERVER CODE -> IT WILL WRITE DATA TO MESSAGE QUEUE */

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
    
    mqid = msgget(key, 0666 | IPC_CREAT);
    if(mqid == -1)
    {
        printf("Unable to create message queue by server!\n");
        return -1;
    }
    
    robj.msgtype = 11;
    strcpy(robj.buffer, "Jay Ganesh...");
    
    iRet = msgsnd(mqid, (void *)&robj, MAX_BUFFER_SIZE, 0);                    // Can specify IPC_NOWAIT so that client does not go to waiting state 
    if(iRet == 0)
    {
        printf("Message sent successfully to the message queue by server.\n");
    }
    
    return 0;
}

