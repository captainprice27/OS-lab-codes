#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// *** WRITE_END --> 1 , READ_END --> 0 , didn't define for ease

// Define the student structure
struct student
{
    int roll;
    char name[100];
    void *data_p;   // void pointer , will point to the data_size field
    int data_size;
};

// Function to fill up the student structures and send them to child process
// parent process will execute
void fill_and_send(int n, int pipe_write_fd)
{
    struct student ss[100];
    for (int i = 0; i < n; i++)
    {
        printf("Enter roll number for student %d: ", i + 1);
        scanf("%d", &ss[i].roll);
        printf("Enter name for student %d: ", i + 1);
        scanf("%s", ss[i].name);

        // Allocate memory for additional information
        // we will be giving department name for additional info
        printf("Enter size of department name (additional info) for student %d: ", i + 1);
        scanf("%d", &ss[i].data_size);
        // The  malloc()  function allocates size bytes and returns a pointer to the allocated memory
        ss[i].data_p = malloc(ss[i].data_size);

        if (ss[i].data_p == NULL)
        {
            perror("malloc failed , space not allocated");
            exit(1);
        }
        printf("Enter department name (additional info) for student %d: ", i + 1);
        scanf("%s", (char *)ss[i].data_p);
    }
    // Write student structures to pipe
    write(pipe_write_fd, ss, sizeof(struct student) * n);
}

// Function to read student structures, sort them, and send back to parent process
// child process will execute that
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
// parent process(P1) executes it after receiving it from child (P2)
void receive_and_print(int n, int pipe_read_fd)
{
    struct student ss[100];
    // Read sorted student structures from pipe
    read(pipe_read_fd, ss, sizeof(struct student) * n);

    // Print student information
    printf("Sorted student information:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Roll: %d, Name: %s, department Name (Add. Info): %s\n", ss[i].roll, ss[i].name, (char *)ss[i].data_p);
        // Free memory allocated for additional information
        free(ss[i].data_p);
    }
}

int main()
{
    int n;  // num of students
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // SINCE WE NEED 2 PIPES
    int pipefd1[2], pipefd2[2];

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1)     // i.e. <0
    {
        perror("pipe not created");
        exit(1);
    }

    // creating child process
    pid_t pid = fork();

    if (pid == -1)  // i.e. pid < 0
    {
        perror("fork failed ");
        exit(1);
    }

    if (pid == 0)   // Child process , which will tread from pipe1 , write in pipe2
    {   // closing unused ends of pipes ...

        close(pipefd1[1]); // Close write end of pipe 1
        close(pipefd2[0]); // Close read end of pipe 2

        receive_sort_and_send(n, pipefd1[0], pipefd2[1]);

        close(pipefd1[0]);
        close(pipefd2[1]);
        exit(1);
    }
    else        // pid > 0 // Parent process which writes in pipe1 , reads from pipe2
    {                      
        close(pipefd1[0]); // Close read end of pipe 1
        close(pipefd2[1]); // Close write end of pipe 2

        fill_and_send(n, pipefd1[1]);

        receive_and_print(n, pipefd2[0]);

        close(pipefd1[1]);
        close(pipefd2[0]);
        wait(NULL); // suspends execution until one of its child processes terminates
        exit(1);
    }

    return 0;
}
