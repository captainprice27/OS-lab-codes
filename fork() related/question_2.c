#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// objective: The given C program calculates the factorial of numbers within a specified range using multiple child processes.
// argc represents the number of command-line arguments passed, and argv is an array of strings containing the arguments.
int main(int argc, char *argv[])
{
    // Two integer variables, n1 and n2, are declared and assigned the integer values converted from the command-line arguments argv[1] and argv[2] using the atoi function.
    // These values represent the range of numbers for which the factorial will be calculated.
    int n1 = atoi(argv[1]), n2 = atoi(argv[2]);

    // f is used to determine if the current process is a child process or the parent process, and prev stores the result of the previous factorial calculation.
    int f = 1, prev = 0;

    // A pid_t variable p is declared to store the process ID.
    pid_t p;

    for (int i = n1; i <= n2; i++)
    {
        // The if condition checks if f is equal to 0. If it is, the loop continues to the next iteration.
        // This condition is used to prevent unnecessary calculations in child processes that are not responsible for calculating the factorial.
        if (f == 0)
        {
            continue;
        }

        // The fork function is called to create a new child process. The return value of fork is stored in p.
        // If p is 0, it means the current process is a child process, and if it's non-zero, it means the current process is the parent process.
        p = fork();
        if (p == 0)
        {
            // f is set to 0 to indicate that this child process has performed the factorial calculation.
            f = 0;
            if (prev == 0)
            {
                int ans = 1, temp = i;
                while (temp)
                {
                    ans *= temp;
                    temp--;
                }
                printf("Factorial calculated at %dth child process: %d\n", i, ans);
                prev = ans;
            }
            // If prev is not 0, it means the factorial for the previous number has already been calculated.
            else
            {
                int ans = prev * i;
                printf("Factorial caluclated at %dth child process: %d\n", i, ans);
                prev = ans;
            }
        }
    }
    return 0;
}
