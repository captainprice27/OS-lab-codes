#include <stdio.h> /* needed also for perror() */
#include <string.h>
#include <stdlib.h>
#include <errno.h>  /* needed  for perror() */
#include <unistd.h> /* needed for execve() */
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigint_handler(int signo)
{
    printf("\nTerminating program...\n");
    exit(0);
}

int main()
{
    signal(SIGINT, sigint_handler); // Register the signal handler for Ctrl+C

    int a = 1 ; 

    while (a)
    {
        char filename[256];

        // Read the name of the executable file
        printf("Enter the name of an executable file (Ctrl+C to exit): ");
        if (fgets(filename, sizeof(filename), stdin) == NULL)
        {
            break; // Exit on EOF (Ctrl+D)
        }

        // Remove the newline character from the filename
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n')
        {
            filename[len - 1] = '\0';
        }

        pid_t pid = fork(); // CREATING A CHILD PROCESS BY FORKING 

        if(pid == -1)
        {
            perror("Error creating child process");

            exit(EXIT_FAILURE); // THIS IS SAME WITH EXIT STATUS AS'1' I.E. PROGRAM TERMINATES
        }

        else if (pid == 0)  // CONDITION OF CHILD PROCESS
        {
            // CHILD PROCESS
            printf("Child process is printing: %s\n", filename);

            // USING EXECVE() FUNCTION TO EXECUTE A PROGRAM THAT PRINTS THE STRING

            char *argv[] = {"/bin/echo", filename, NULL};
            execve("/bin/echo", argv, NULL);

            // IF EXECVE FACES A PROBLEM EXECUTING
            perror("Error executing the program");
            exit(EXIT_FAILURE);         // SAME AS EXIT(1)
        }
        else    // HERE pid = 1 , I.E. PARENT PROCESS 
        {
            // PAENT PROCESS

            int status;
            waitpid(pid, &status, 0);
            //pid_t waitpid(pid_t pid, int *status, int options)

            // WIFEXITED(status) : returns true if the child terminated normally.

            if (WIFEXITED(status))
            {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            }
            else
            {
                printf("Child process terminated abnormally\n");
            }
        }
    }

    return 0;
}
