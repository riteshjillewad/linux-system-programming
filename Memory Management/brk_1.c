#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    void *current_break_point = NULL;

    current_break_point = sbrk(0);
    printf("Current break point is: %p\n", current_break_point);

    return 0;
}
