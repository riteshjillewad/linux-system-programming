#include<stdio.h>
#include<unistd.h>

int main() 
{
    void *break1 = NULL;
    void *break2 = NULL;

    // sbrk(0) returns current break without changing it
    break1 = sbrk(0);
    printf("Break point 1: %p\n", break1);
    
    // Another call returns same address
    break2 = sbrk(0);
    printf("Break point 2: %p\n", break2);
    
    if(break1 == break2) 
    {
        printf("Both queries returned same address ✓\n");
    }
    
    return 0;
}