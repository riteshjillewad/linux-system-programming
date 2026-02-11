#include<stdio.h>
#include<stdlib.h>

void main()
{
    // printf("Jay Ganesh...\n");
    printf("Hello world\n");

    exit(0);
}

/*

Now here, if run this code using make, we will get the output as Jat Ganesh...
But here is one catch, now modify the printf statement, and again run make command.
We expect the output to be Hello world, but the output that is shown is Jay Ganesh.

Why?

Here, in the makefile, we don't provide the dependencies for the target, so once the make command is runned,
it is compiled and the output is shown as Jay Ganesh... But when we modify the main.c, and again run the make command
the new message is not displayed. It is because in 2nd run make checks if the file exists, and checks for dependencies
, so it assumes everything is perfect and upto data, and does not send the main.c to compiler, so we get the old
output displayed (as old executable is unchanged).

*/