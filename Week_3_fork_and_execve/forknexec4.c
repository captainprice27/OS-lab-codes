/*This is an extension of the previous assignment titled "Child Processes execute different executable files as "told" by the user: Problem 1." Hence, you may please edit the final file (say, forkNexec3.c) for the present assignment.

Please note that often programs take command line arguments (Eg., the programs you write having a main() function defined as "int main(int argc, char *argv[]) {.....}". For example, the unix command "ls" (/bin/ls being the executable file) can be executed as "ls -l" ("-l" is the command line argument) producing an output like:
total 488
-rw-rw-r-- 1 manas manas 486286 Nov 10  2022 8086.zip
drwxrwxr-x 2 manas manas   4096 Nov 21  2022 ASM
drwx------ 2 manas manas   4096 Nov 10  2022 bin

or can be executed as "ls -l 8086*" ("-l" and "8086*" being the command line arguments) producing output like:
-rw-rw-r-- 1 manas manas 486286 Nov 10  2022 8086.zip

In the present assignment, the program, in every iteration of the infinite-loop, reads a whole line, where the 1st word of the line is to be treated as the name of an executable file, and the remaining words are to be treated as the command line arguments to the executable file. And the child process, now, should execute the file by passing those command line arguments.*/

// FORKNEXEC3.C IS MODIFIED HERE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

    while (1)
    {
        char input[256];

        // Read the whole line where the first word is executable file and the rest are arguments
        printf("Enter the command (Ctrl+C to exit): ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        // Remove the newline character from the input
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Error creating child process");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)  // CONDITION OF CHILLD PROCESS
        {
            
            char *token = strtok(input, " ");   //The strtok() method splits str[] according to given delimiters and returns the next token (GFG)
            char *argv[256];
            int i = 0;

            while (token != NULL)
            {
                argv[i++] = token;
                token = strtok(NULL, " ");
            }

            argv[i] = NULL;

            // Execute the specified program with provided arguments
            execvp(argv[0], argv);

            // execvp returns only on error
            perror("Error executing the program");
            exit(EXIT_FAILURE);
        }
        else
        {
            // PARENT PROCESS PID = 1
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
