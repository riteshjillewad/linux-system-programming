// This is the client code, that will use the shared object

#include<stdio.h>
#include<dlfcn.h>

int main()
{
    void *handle = NULL;
    char *error = NULL;
    int choice = 0, val = 0;

    void(*increment_fp)(int);
    void(*display_fp)();
    void(*reset_fp)();

    // Load library
    handle = dlopen("./question7_server.so", RTLD_LAZY);
    if(!handle)
    {
        printf("dlopen failed: %s\n", dlerror());
        return -1;
    }

    // clear old errors
    dlerror();

    // Load symbols
    increment_fp = (void(*)(int)) dlsym(handle,"increment");
    if((error = dlerror()) != NULL) goto fail;

    display_fp = (void(*)()) dlsym(handle,"display");
    if((error = dlerror()) != NULL) goto fail;

    reset_fp = (void(*)()) dlsym(handle,"reset");
    if((error = dlerror()) != NULL) goto fail;

    while(1)
    {
        printf("\n============================\n");
        printf("1. Increment Counter\n");
        printf("2. Display Counter\n");
        printf("3. Reset Counter\n");
        printf("4. Exit\n");
        printf("============================\n");
        printf("Enter choice: \n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("Enter value: \n");
                scanf("%d",&val);
                increment_fp(val);
                break;

            case 2:
                display_fp();
                break;

            case 3:
                reset_fp();
                break;

            case 4:
                dlclose(handle);
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

fail:
    printf("dlsym error: %s\n", error);
    dlclose(handle);
    return -1;
}


/* We use the goto statement here, which allows the program to jump to some part of the code, giving you more control over its execution.*/