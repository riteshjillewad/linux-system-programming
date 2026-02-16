// This is the server code, of which we will create the .so file

#include<stdio.h>

// Function to count the lowercase letters in string
void count(char string[])
{
    int countUpperCase = 0;
    int countLowerCase = 0;
    int countDigits = 0;
    int i = 0;

    while(string[i] != '\0')
    {
        if((string[i] >= 'a') && (string[i] <= 'z'))
        {
            countLowerCase++;
        }
        else if((string[i] >= 'A') && (string[i] <= 'Z'))
        {
            countUpperCase++;
        }
        else if((string[i] >= '0') && (string[i] <= '9'))
        {
            countDigits++;
        }

        i++;
    }

    printf("String: %s\n", string);
    printf("Total lowercase letters: %d\n", countLowerCase);
    printf("Total uppercase letters: %d\n", countUpperCase);
    printf("Total digits: %d\n", countDigits);
}