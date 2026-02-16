// This is the server code of which the shared library will be created

#include<stdio.h>

int globalVariable = 0;

// Function used to increment the variable by value times
void increment(int val)
{
    globalVariable += val;
}

// Function used to display the variable
void display()
{
    printf("Global Variable: %d\n", globalVariable);
}

// Function used to reset the global varialbe
void reset()
{
    globalVariable = 0;
    printf("Reset successful.\n");
}