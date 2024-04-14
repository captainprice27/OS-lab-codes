#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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

    // Pass the ith largest number to the parent process
    exit(arr[i - 1]);
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
        pid_t pid = fork();

        if (pid < 0)
        {
            fprintf(stderr, "Fork failed.\n");
            return 1;
        }
        else if (pid == 0)
        {
            // Child process
            findIthLargest(arr, n, i);
        }
    }

    int *sortedArray = (int *)malloc(n * sizeof(int));

    // Wait for all child processes to complete
    for (int i = 1; i <= n; i++)
    {
        int status;
        wait(&status);

        // Retrieve ith largest number from exit status
        int ithLargest = WEXITSTATUS(status);

        // Store the ith largest number in the sorted array
        sortedArray[i - 1] = ithLargest;
    }

    // Print the sorted array in descending order
    printf("\nSorted Array in Descending Order:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", sortedArray[i]);
    }
    printf("\n");

    // Free allocated memory
    free(arr);
    free(sortedArray);

    return 0;
}

