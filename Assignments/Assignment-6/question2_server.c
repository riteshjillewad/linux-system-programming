// This is server code, we will create the .so file of this server
#include<stdbool.h>

int addition(int a, int b)
{
    int ans = 0;
    ans = a + b;
    return ans;
}

int subtraction(int a, int b)
{
    int ans = 0;
    ans = a - b;
    return ans;
}

bool checkEvenOdd(int a)
{
    return (a % 2 == 0);                // It will return true if a is divisible by 2, else will return false
}

bool checkPrime(int a)
{
    if(a <= 1)
    {
        return false;
    }

    for(int i = 2; i < a; i++)
    {
        if((a % i) == 0)
        {
            return false;
        }
    }
    return true;
}

