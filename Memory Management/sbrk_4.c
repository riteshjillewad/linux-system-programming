#include<stdio.h>
#include<unistd.h>

/* THIS CODE PROVES THAT MEMORY ALLOCATED ARE IN MULTIPLES OF PAGE SIZE */

int main() 
{
    void *start = NULL;
    void *after = NULL;
    long actual = 0;
    long page_size = 0;

    start = sbrk(0);
    printf("Initial break: %p\n", start);
    
    // Request just 100 bytes
    printf("\nRequesting 100 bytes...\n");
    sbrk(100);
    
    after = sbrk(0);
    printf("New break: %p\n", after);
    
    actual = (char *)after - (char *)start;
    printf("Actual increase: %ld bytes\n", actual);
    
    // Check page size
    page_size = sysconf(_SC_PAGESIZE);
    printf("System page size: %ld bytes\n", page_size);
    
    if(actual >= page_size) 
    {
        printf("Kernel allocated at least one full page!\n");
    }
    
    return 0;
}