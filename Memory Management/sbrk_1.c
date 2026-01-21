#include<stdio.h>
#include<unistd.h>

int main() 
{
    // Current break without changing it
    void *initial = sbrk(0);
    printf("Initial program break: %p\n", initial);
    
    // Allocating 1024 bytes
    void *prev = sbrk(1024);
    if (prev == (void *) -1) 
    {
        perror("sbrk failed");
        return 1;
    }
    
    printf("Previous break (before allocation): %p\n", prev);
    printf("Allocated 1024 bytes\n");
    
    // Finding new break
    void *current = sbrk(0);
    printf("Current break: %p\n", current);
    printf("Difference: %ld bytes\n", (char *)current - (char *)prev);
    
    return 0;
}
