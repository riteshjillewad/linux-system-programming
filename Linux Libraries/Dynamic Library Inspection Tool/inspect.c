////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:        inspect.c
//  Description: This code is used to take the shared object path and symbol name as command line
//               arguments, and perform operations on them
//  Input:       shared object path, symbol name
//  Output:      void
//  Author:      Ritesh Jillewad
//  Date:        16-02-2026
////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include <dlfcn.h>

////////////////////////////////////////////////////////////////////////////////////////////////
//  Input: ./inspect      library path      symbol name
//          argv[0]         argv[1]           argv[2]
//          
//          argc = 3
////////////////////////////////////////////////////////////////////////////////////////////////    

int main(int argc, char *argv[])
{
    void *handle = NULL;
    void *sym = NULL;
    char *error = NULL;

    // First we check the parameters condition
    if(argc != 3)
    {
        printf("ERROR: Invalid number of arguments!\n");
        printf("Try: ./inspect  library path  symbol name\n");
        return -1;
    }

    /* STEP 1: LOADING THE LIBRARY */
    printf("Loading library: %s...\n", argv[1]);
    handle = dlopen(argv[1], RTLD_LAZY);
    if(handle == NULL)
    {
        printf("ERROR: %s\n", dlerror());
        return -1;
    }
    printf("Library %s loaded successfully.\n", argv[1]);

    // Clearing old errors(for dlsym)
    dlerror();

    /* STEP 2: FINDING THE SYMBOL FROM THE LOADED LIBRARY */
    printf("Searching for symbol: %s\n", argv[2]);
    sym = dlsym(handle, argv[2]);

    // Here we check for error if any due to sym
    error = dlerror();
    if(error != NULL)
    {
        printf("Symbol not found: %s\n", error);
        dlclose(handle);
        return -1;
    }
    printf("Symbol FOUND!\n");
    printf("Address of '%s' = %p\n", argv[2], sym);

    dlclose(handle);
    return 0;
}
