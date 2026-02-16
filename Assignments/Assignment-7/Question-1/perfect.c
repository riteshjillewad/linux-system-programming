// This file contains the code to check if the number is perfect or not

#include<stdbool.h>

// We will use extern, as the function will come from another file (library)
extern int sumOfFactors(int);

bool isPerfect(int num)
{
    int sum = 0;

    // Filter
    if(num <= 0)
    {
        return false;
    }

    sum = sumOfFactors(num);                            // Passed to the extern function

    return (sum == num);
}