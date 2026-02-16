#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>

int main()
{
    void *handle = NULL;
    char *error = NULL;
    char str[100];

    void (*count_fp)(char *);

    // Load shared library
    handle = dlopen("./question8_server.so", RTLD_LAZY);
    if(handle == NULL)
    {
        printf("dlopen failed: %s\n", dlerror());
        return -1;
    }

    dlerror();

    // Get function address
    count_fp = (void(*)(char*)) dlsym(handle, "count");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    printf("Enter a string: \n");
    scanf("%s", str);   // SIMPLE INPUT (no spaces)

    // Call library function
    count_fp(str);

    dlclose(handle);
    return 0;
}
