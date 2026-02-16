// This is client code, we will load our .so file here, and use the functions

#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#include<stdbool.h>

int main()
{
    void *handle = NULL;

    int(*add_fp)(int,int);
    int(*sub_fp)(int,int);
    bool(*evenodd_fp)(int);
    bool(*prime_fp)(int);

    int a = 0, b = 0;
    char *error = NULL;

    handle = dlopen("./question2_server.so", RTLD_LAZY);
    if(!handle)
    {
        printf("dlopen failed: %s\n", dlerror());
        return -1;
    }
    printf("Library loaded successfully...\n");

    dlerror();

    // Addition
    add_fp = (int(*)(int,int))dlsym(handle, "addition");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym addition error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    // Subtraction
    sub_fp = (int(*)(int,int))dlsym(handle, "subtraction");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym subtraction error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    // Check even or odd
    evenodd_fp = (bool(*)(int))dlsym(handle, "checkEvenOdd");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym checkEvenOdd error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    // Check prime
    prime_fp = (bool(*)(int))dlsym(handle, "checkPrime");
    if((error = dlerror()) != NULL)
    {
        printf("dlsym checkPrime error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    printf("Enter first number: \n");
    scanf("%d", &a);

    printf("Enter second number: \n");
    scanf("%d", &b);

    printf("Addition: %d\n", add_fp(a,b));
    printf("Subtraction: %d\n", sub_fp(a,b));

    if(evenodd_fp(a))
    {
        printf("%d is Even\n", a);
    }
    else
    {
        printf("%d is Odd\n", a);
    }

    if(prime_fp(a))
    {
        printf("%d is Prime\n", a);
    }
    else
    {
        printf("%d is Not Prime\n", a);
    }

    dlclose(handle);
    return 0;
}
