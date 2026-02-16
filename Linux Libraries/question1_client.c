// This is client code, we will load our .so file here, and use the functions

#include<stdio.h>
#include<dlfcn.h>
#include<string.h>
#include<stdlib.h>

int addition(int, int);
int subtraction(int, int);

int main()
{
    void *handle = NULL;

    int ret = 0;
    int (*fp)(int, int);
    int no1 = 0, no2 = 0;

    // Step 1: We will load our .so library
    handle = dlopen("./question1_server.so", RTLD_LAZY);
    if(handle == NULL)
    {
        printf("ERROR: Unable to load the library!\n");
        return -1;
    }
    printf("Library loaded successfully...\n");

    printf("Enter first number: \n");
    scanf("%d", &no1);

    printf("Enter second number: \n");
    scanf("%d", &no2);

    // Step 2: Now we need to get the address of the functions from the shared library
    // Addition
    fp = (int(*)(int, int))dlsym(handle, "addition");
    if(fp == NULL)
    {
        printf("Unable to get the address of function!\n");
        dlclose(handle);
        return -1;
    }
    
    ret = fp(no1, no2);
    printf("Addition of %d and %d is: %d\n", no1, no2, ret);

    // Subtraction
    fp = (int(*)(int, int))dlsym(handle, "subtraction");
    if(fp == NULL)
    {
        printf("Unable to get the address of function!\n");
        dlclose(handle);
        return -1;
    }
    
    ret = fp(no1, no2);
    printf("Subtraction of %d and %d is: %d\n", no1, no2, ret);

    dlclose(handle);
    return 0;
}