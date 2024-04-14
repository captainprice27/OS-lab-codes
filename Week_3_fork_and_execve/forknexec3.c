// forkNexec2.c IS COPY PASTED WITH SOME MODIFICATIONS
// now the child process, in place of printing the string, executes a file named by that string. Now too, the parent process waits for the termination of the child //// process before resuming the next iteration of the infinite-loop.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// PROCESS FOR TERMINATION

void sigint_handler(int signo)
{
    printf("\nTerminating program...\n");
    exit(0);
}

int main()
{
    signal(SIGINT, sigint_handler); // Register the signal handler for Ctrl+C

    int a  = 1 ; 

    while (a)
    {
        char filename[256];

        // Read the name of the executable file
        printf("Enter the name of an executable file (Ctrl+C to exit): ");
        if (fgets(filename, sizeof(filename), stdin) == NULL)
        {
            break;
        }

        // Remove the newline character from the filename
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n')
        {
            filename[len - 1] = '\0';
        }

        pid_t pid = fork(); // CHILD PROCESS CREATED

        if (pid == -1)
        {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // CHILD PROCESS
            printf("Child process is executing: %s\n", filename);

            char *argv[] = {filename, NULL};
            execve(filename, argv, NULL);

            perror("Error executing the program");
            exit(EXIT_FAILURE); // STATED EARLIER THAT EXIT(1) IS SAME AS THIS
        }
        else
        {
            // PARENT PROCESS
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                printf("Child process exited normally with status %d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                printf("Child process terminated abnormally by signal %d\n", WTERMSIG(status));
            }
            else
            {
                printf("Child process terminated abnormally\n");
            }
        }
    }

    return 0;
}
