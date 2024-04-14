#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// objective: This C code calculates the factorial of numbers from 1 to a given positive integer n using multiple child processes created by forking

// THIS IS THE FACTORIAL FUNCTION 
unsigned int factorial(int n)
{
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main(int argc, char *argv[])
{
    // Converts the first command-line argument (argv[1]) to an integer n.
    int n = atoi(argv[1]);

    // Initializes a variable pid_t p to store process IDs.
    pid_t p;

    /* Inside the loop:
    Parent process calls fork() to create a child process.
     Checks the return value of fork():
     If less than 0, prints an error message indicating fork failure.
     If 0, executes code for the child process: ( for child process , p==0 for fork)
     Calculates the factorial of i using the factorial() function.
     Prints the factorial of i and exits from the child process.
     The parent process (original process) continues after the loop and terminates.*/

    for (int i = 1; i <= n; i++)
    {
        p = fork();

        if (p < 0)
        { 
            printf("Fork failed.\n");
            return 1;
        }
        else if (p == 0)
        {
            // Child process
            unsigned int fact = factorial(i);
            printf("Factorial of %d: %d\n", i, fact);
            exit(0);
        }
    }

    return 0;
}
