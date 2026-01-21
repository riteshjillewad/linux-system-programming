#include<stdio.h>
#include<unistd.h>

int main() 
{

    void *start = NULL;
    void *allocated = NULL;
    void *after_alloc = NULL;
    void *freed = NULL;
    void *after_free = NULL;

    start = sbrk(0);
    printf("Initial break: %p\n", start);
    
    // Allocate 4096 bytes
    printf("\nAllocating 4096 bytes...\n");
    allocated = sbrk(4096);
    printf("Previous break: %p\n", allocated);
    
    after_alloc = sbrk(0);
    printf("Current break: %p\n", after_alloc);
    printf("Heap size: %ld bytes\n", (char *)after_alloc - (char *)start);
    
    // Deallocate 2048 bytes
    printf("\nDeallocating 2048 bytes...\n");
    freed = sbrk(-2048);
    printf("Previous break: %p\n", freed);
    
    after_free = sbrk(0);
    printf("Current break: %p\n", after_free);
    printf("Heap size: %ld bytes\n", (char *)after_free - (char *)start);
    
    return 0;
}
