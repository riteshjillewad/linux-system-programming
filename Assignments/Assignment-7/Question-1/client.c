#include<stdio.h>
#include<dlfcn.h>
#include<stdbool.h>

int main()
{
    void *handle = NULL;
    char *error = NULL;
    int num = 0;

    bool(*checkPerfect_fp)(int);

    // Step 1: Load the library
    handle = dlopen("./libperfect.so", RTLD_LAZY);
    if(handle == NULL)
    {
        printf("ERROR: %s\n", dlerror());
        return -1;
    }

    // Clean the previous errors
    dlerror();

    // Now we need to get the address of the function
    checkPerfect_fp = (bool(*)(int))dlsym(handle, "isPerfect");
    error = dlerror();
    if(error != NULL)
    {
        printf("ERROR: %s\n", error);
        dlclose(handle);
        return -1;
    }

    // Since no error occured, we pass the number to the function
    printf("Enter number: \n");
    scanf("%d", &num);

    if(checkPerfect_fp(num) == true)
    {
        printf("%d is a perfect number.\n", num);
    }
    else
    {
        printf("%d is not a perfect number.\n", num);
    }

    dlclose(handle);
    return 0;
}