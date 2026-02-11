#include<stdio.h>
#include "helper.h"

int main()
{
    int a = 0;
    int b = 0;

    printf("Enter first number: \n");
    scanf("%d", &a);

    printf("Enter second number: \n");
    scanf("%d", &b);

    printf("Addition of %d and %d is: %d\n", a, b, add(a, b));
    return 0;
}