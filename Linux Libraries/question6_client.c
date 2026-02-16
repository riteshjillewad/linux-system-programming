#include <stdio.h>
#include <dlfcn.h>

int main()
{
    void *handle = NULL;
    char *err = NULL;

    int (*add_fp)(int,int);

    // NOTE: No path — only library name
    handle = dlopen("libdemo.so", RTLD_LAZY);
    if(!handle)
    {
        printf("dlopen failed: %s\n", dlerror());
        return -1;
    }

    add_fp = (int(*)(int,int)) dlsym(handle,"add");
    if((err = dlerror()) != NULL)
    {
        printf("dlsym error: %s\n", err);
        return -1;
    }

    printf("Addition result: %d\n", add_fp(10,20));

    dlclose(handle);
    return 0;
}


/*
    When we try to run this, it will give us the error: dlopen failed: libdemo.so: cannot open shared object file: No such file or directory
    So,
        we need to provide them with the path.
        export LD_LIBRARY_PATH=$PWD/mylib              
        ./client

        Without LD_LIBRARY_PATH:
        Dynamic loader cannot locate the shared library because the custom directory is not part of the default search paths.

        With LD_LIBRARY_PATH:
        Loader successfully finds the library because LD_LIBRARY_PATH temporarily adds the custom directory to the runtime search path.
*/