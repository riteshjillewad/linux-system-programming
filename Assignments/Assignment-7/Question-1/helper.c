// This file contains the helper functions that will be used by the isPerfect() function

int sumOfFactors(int num)
{
    int i = 0;
    int sum = 0;

    for(i = 1; i < num; i++)
    {
        if(num % i == 0)
        {
            sum = sum + i;
        }
    }

    return sum;
}