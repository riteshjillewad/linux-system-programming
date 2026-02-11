#include<stdio.h>
#include "ritesh.h"

int main()
{
    int iRet = 0;
    int iNo1 = 0, iNo2 = 0;

    printf("Enter first number: \n");
    scanf("%d", &iNo1);

    printf("Enter second number: \n");
    scanf("%d", &iNo2);

    iRet = addition(iNo1, iNo2);
    printf("Addition of %d and %d is: %d\n", iNo1, iNo2, iRet);

    iRet = subtraction(iNo1, iNo2);
    printf("Subtraction of %d and %d is: %d\n", iNo1, iNo2, iRet);

    iRet = multiplication(iNo1, iNo2);
    printf("Multiplication of %d and %d is: %d\n", iNo1, iNo2, iRet);

    return 0;
}