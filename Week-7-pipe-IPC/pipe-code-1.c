#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// LETS TAKE WRITE = 1 , READ = 0
// Define the student structure
struct student
{
    int roll;
    char name[100];
};

// Function to fill up the student structures and send them to child process
void fill_and_send(int n, int pipe_write_fd)
{
    struct student ss[100];
    for (int i = 1; i <= n; i++)
    {
        printf("Enter roll number for student %d: ", i);
        scanf("%d", &ss[i].roll);
        printf("Enter name for student %d: ", i);
        scanf("%s", ss[i].name);
    }
    // Write student structures to pipe
    write(pipe_write_fd, ss, sizeof(struct student) * n);
    // *n for n inputs  , to be taken from user
}

// Function to read student structures, sort them, and send back to parent process
void receive_sort_and_send(int n, int pipe_read_fd, int pipe_write_fd)
{
    struct student ss[100];
    // Read student structures from pipe
    read(pipe_read_fd, ss, sizeof(struct student) * n);

    // Sorting student structures based on roll number (using bubble sort)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (ss[j].roll > ss[j + 1].roll)
            {
                // Swap
                struct student temp = ss[j];
                ss[j] = ss[j + 1];
                ss[j + 1] = temp;
            }
        }
    }

    // Write sorted student structures back to parent process
    write(pipe_write_fd, ss, sizeof(struct student) * n);
}

// Function to receive and print student structures
void receive_and_print(int n, int pipe_read_fd)
{
    struct student ss[100];
    // Read sorted student structures from pipe
    read(pipe_read_fd, ss, sizeof(struct student) * n);

    // Print student information
    printf("student info sorted by roll no:\n");
    for (int i = 1; i <= n; i++)
    {
        printf("Roll: %d, Name: %s\n", ss[i].roll, ss[i].name);
    }
}

int main()
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // since we need to use 2 different pipes
    int pipefd1[2], pipefd2[2];

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0) // Child process
    {
        close(pipefd1[1]); // Close write end of pipe 1
        close(pipefd2[0]); // Close read end of pipe 2

        receive_sort_and_send(n, pipefd1[0], pipefd2[1]);

        close(pipefd1[0]);
        close(pipefd2[1]);
        exit(1);
    }
    else // Parent process
    {
        close(pipefd1[0]); // Close read end of pipe 1
        close(pipefd2[1]); // Close write end of pipe 2
        fill_and_send(n, pipefd1[1]);

        receive_and_print(n, pipefd2[0]);
        
        close(pipefd1[1]);
        close(pipefd2[0]);
        wait(NULL);
        exit(1);
    }

    return 0;
}
