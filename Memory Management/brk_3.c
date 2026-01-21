#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/* THE USABLE MEMORY RANGE IS: [current_break_point , new_break_point] */

int main()
{
    void *current_break_point = NULL;
    void *new_break_point = NULL;

    current_break_point = sbrk(0);
    printf("Current break point is: %p\n", current_break_point);

    new_break_point = (char *)current_break_point + 4096;

    if(brk(new_break_point) == 0)
    {
        printf("Successfully moved the break point to: %p\n", new_break_point);
        printf("Heap increased by 4096 bytes\n");
    }
    else
    {
        perror("brk failed");
        return -1;
    }

    strcpy((char *)current_break_point, "Jay Ganesh...");

    printf("Data from new memory: %s\n", (char *)current_break_point);
    return 0;
}
