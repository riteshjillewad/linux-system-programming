/* THIS IS MESSAGE QUEUE SERVER CODE -> IT WILL WRITE DATA TO MESSAGE QUEUE */

#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>

int main()
{
    key_t key;
    int mqid = 0;
    
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
    
    return 0;
}

