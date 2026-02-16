#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *lazyHandle = NULL;
    void *nowHandle = NULL;
    char *err = NULL;

    int (*broken_fp)(int);

    printf("RTLD_LAZY:\n");
    lazyHandle = dlopen("./question5_server.so", RTLD_LAZY);
    if(!lazyHandle)
    {
        printf("%s\n", dlerror());
    }
    else
    {
        broken_fp = (int(*)(int)) dlsym(lazyHandle,"broken");
        if((err = dlerror()) != NULL)
        {
            printf("dlsym error: %s\n", err);
        }
        else
        {
            printf("Calling broken()...\n");
            broken_fp(5);   
        }
    }

    printf("\nRTLD_NOW:\n");
    nowHandle = dlopen("./question5_server.so", RTLD_NOW);
    if(!nowHandle)
    {
        printf("%s\n", dlerror());
    }
    else
    {
        printf("Loaded with RTLD_NOW (unexpected)\n");
    }

    return 0;
}
