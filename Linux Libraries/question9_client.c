#include<stdio.h>
#include<dlfcn.h>

#define FUNC_COUNT 4

int main()
{
    void *handle = NULL;
    char *error = NULL;

    // Array of function pointers
    int (*funcs[FUNC_COUNT])(int,int);

    // Function names to load
    char *names[FUNC_COUNT] = { "add", "sub", "mul", "divide" };

    int a = 20, b = 5;

    handle = dlopen("./question9_server.so", RTLD_LAZY);
    if(!handle)
    {
        printf("dlopen failed: %s\n", dlerror());
        return -1;
    }

    dlerror(); 

    for(int i = 0; i < FUNC_COUNT; i++)
    {
        funcs[i] = (int(*)(int,int)) dlsym(handle, names[i]);
        if((error = dlerror()) != NULL)
        {
            printf("dlsym error for %s: %s\n", names[i], error);
            dlclose(handle);
            return -1;
        }
    }

    printf("Using function pointer array:\n\n");
    for(int i = 0; i < FUNC_COUNT; i++)
    {
        printf("%s(%d,%d) = %d\n", names[i], a, b, funcs[i](a,b));
    }

    dlclose(handle);
    return 0;
}
