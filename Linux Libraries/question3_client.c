// This is client code, we will load our .so file here, and use the functions

#include<stdio.h>
#include<dlfcn.h>

int main()
{
    void *handle = NULL;
    int ret = 0;
    int no1 = 0, no2 = 0;
    int choice = 0;
    char *error = NULL;

    int(*add_fp)(int, int);
    int(*sub_fp)(int, int);
    int(*mul_fp)(int, int);
    int(*div_fp)(int, int);

    // Step 1: Load the library
    handle = dlopen("./question3_server.so", RTLD_LAZY);
    if(handle == NULL)
    {
        printf("dlopen failed: %s\n", dlerror());
        return -1;
    }
    printf("Library loaded successfully...\n");

    // Step 2: Check for the previous errors
    dlerror();

    // Step 3: Load the address of functions from the library
    // Addition
    add_fp = (int(*)(int, int))dlsym(handle, "addition");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym addition error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    // Substraction
    sub_fp = (int(*)(int, int))dlsym(handle, "substraction");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym substraction error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    // Multiplication
    mul_fp = (int(*)(int, int))dlsym(handle, "multiplication");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym multiplication error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    // Division
    div_fp = (int(*)(int, int))dlsym(handle, "division");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym division error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    // Step 4: Now we need to ask the user for options
    while(1)
    {
        printf("=================================\n");
        printf("ARITHMETIC LIBRARY\n");
        printf("=================================\n");
        printf("1. Addition.\n");
        printf("2. Substraction.\n");
        printf("3. Multiplication.\n");
        printf("4. Division.\n");
        printf("5. Exit.\n");
        printf("=================================\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        if(choice == 5)
        {
            printf("Exiting...\n");
            break;
        }

        printf("Enter first number: \n");
        scanf("%d", &no1);

        printf("Enter second number: \n");
        scanf("%d", &no2);

        switch(choice)
        {
            case 1: 
                printf("Addition of %d and %d is: %d\n", no1, no2, add_fp(no1, no2));
                break;

            case 2: 
                printf("substraction of %d and %d is: %d\n", no1, no2, sub_fp(no1, no2));
                break;

            case 3: 
                printf("Multiplication of %d and %d is: %d\n", no1, no2, mul_fp(no1, no2));
                break;

            case 4: 
                if(no2 == 0)
                {
                    printf("Division by zero not allowed!\n");
                }
                else
                {
                    printf("Division of %d and %d is: %d\n", no1, no2, div_fp(no1,no2));
                }
                break;

            default:
                printf("Invalid choice.\n");
        }
    }

    dlclose(handle);
    return 0;
}