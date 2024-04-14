#include <stdio.h> 
#include <stdlib.h>   // for malloc() , free() etc ...
#include <unistd.h>   // for fork() and exit() etc...
#include <sys/wait.h> // for wait()
#include <sys/types.h>  // for pid_t etc ...

void findIthLargest(int *arr, int n, int i)
{
    // Sort the array in descending order
    for (int j = 0; j < n - 1; j++)
    {
        for (int k = 0; k < n - j - 1; k++)
        {
            if (arr[k] < arr[k + 1])
            {
                // Swap elements if they are in the wrong order
                int temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
            }
        }
    }

    // Print the ith largest number
    printf("Process %d: %dth Largest Number: %d\n", i, i, arr[i - 1]);
}

int main()
{
    int n;

    // Get the size of the array from the user
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        fprintf(stderr, "Invalid array size.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));

    // Populate the array with user input
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Create child processes
    for (int i = 1; i <= n; i++)
    {
        pid_t p = fork();

        if (p < 0)
        {
            fprintf(stderr, "Fork failed.\n");
            return 1;
        }
        else if (p == 0)
        {
            // Child process
            findIthLargest(arr, n, i);
            exit(0);
        }
    }

    // Wait for all child processes to complete
    for (int i = 1; i <= n; i++)
    {
        wait(NULL);
    }

    // Free allocated memory
    free(arr);

    return 0;
}

