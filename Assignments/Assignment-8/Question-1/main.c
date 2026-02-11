////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:          main.c
// Description:   This file accepts two integers and prints it's addition
// Input:         Integer
// Output:        Addition of Integet
// Author:        Ritesh Jillewad
// Date:          11-02-2025
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int iNo1 = 0;
    int iNo2 = 0;
    int iSum = 0;
    
    printf("Enter first number: \n");
    scanf("%d", &iNo1);
    
    printf("Enter second number: \n");
    scanf("%d", &iNo2);
    
    iSum = iNo1 + iNo2;
    printf("Addition of %d and %d is: %d\n", iNo1, iNo2, iSum);
    
    return 0;
}
