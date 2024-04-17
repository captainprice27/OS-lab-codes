#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

// Function to handle internal commands
// supports for upto 5 commands cd , pwd , mkdir , exit and exit 
void handle_internal_command(char *args[])
{
    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "mysh: cd: missing argument\n");
        }
        else
        {
            if (chdir(args[1]) != 0)    // chdir --> change directory
            {
                perror("mysh: cd");
            }
        }
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("mysh: pwd");
        }
    }
    else if (strcmp(args[0], "clear") == 0)
    {
        system("clear");
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(args[0], "mkdir") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "mysh: mkdir: missing argument\n");
        }
        else
        {
            if (mkdir(args[1], 0777) != 0)
            {
                perror("mysh: mkdir");
            }
        }
    }
    else
    {
        fprintf(stderr, "mysh: %s: command not found\n", args[0]);
    }
}

int main()
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    char *token;
    char *delimiters = " \t\n";
    int status;
    int pipefd[2];

    while (1)
    {
        printf("mysh> ");

        // Read command from stdin
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break; // Exit on EOF
        }

        // Parse command into tokens
        token = strtok(command, delimiters);
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, delimiters);
        }
        args[i] = NULL;

        // Check for IO redirection
        int infile = STDIN_FILENO;   // Default to stdin
        int outfile = STDOUT_FILENO; // Default to stdout

        for (int j = 0; args[j] != NULL; j++)
        {
            if (strcmp(args[j], "<") == 0)
            {
                infile = open(args[j + 1], O_RDONLY);
                if (infile < 0)
                {
                    perror("open");
                    exit(1);
                }
                args[j] = NULL; // Remove "<" from args
                j++;            // Skip the filename
            }
            else if (strcmp(args[j], ">") == 0)
            {
                outfile = open(args[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (outfile < 0)
                {
                    perror("open");
                    exit(1);
                }
                args[j] = NULL; // Remove ">" from args
                j++;            // Skip the filename
            }
        }

        // Handle internal commands
        if (args[0] != NULL)
        {
            handle_internal_command(args);
        }

        // Check for pipe
        char *pipe_token = NULL;
        for (int j = 0; args[j] != NULL; j++)
        {
            if (strcmp(args[j], "|") == 0)
            {
                pipe_token = args[j];
                args[j] = NULL; // Terminate args before the pipe
                break;
            }
        }

        // Create pipe if pipe_token is found
        if (pipe_token != NULL)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                exit(1);
            }
        }

        // Fork and execute external command
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            if (pipe_token != NULL)
            {
                // If pipe is present, redirect stdout to write end of pipe
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
                close(pipefd[0]); // Close read end of pipe
                close(pipefd[1]); // Close write end of pipe
            }

            // Redirect input/output files if necessary
            if (infile != STDIN_FILENO)
            {
                if (dup2(infile, STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
                close(infile);
            }

            if (outfile != STDOUT_FILENO)
            {
                if (dup2(outfile, STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
                close(outfile);
            }

            // Execute command
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        }
        else
        {
            // Parent process
            waitpid(pid, &status, 0);

            // If pipe is present, execute second command
            if (pipe_token != NULL)
            {
                // Fork again
                pid_t pid2 = fork();
                if (pid2 < 0)
                {
                    perror("fork");
                    exit(1);
                }
                else if (pid2 == 0)
                {
                    // Child process
                    // Redirect stdin to read end of pipe
                    if (dup2(pipefd[0], STDIN_FILENO) == -1)
                    {
                        perror("dup2");
                        exit(1);
                    }
                    close(pipefd[0]); // Close read end of pipe
                    close(pipefd[1]); // Close write end of pipe

                    // Execute second command
                    execvp(args[i + 1], &args[i + 1]);
                    perror("execvp");
                    exit(1);
                }
                else
                {
                    // Parent process
                    close(pipefd[0]); // Close read end of pipe
                    close(pipefd[1]); // Close write end of pipe
                    waitpid(pid2, &status, 0);
                }
            }
        }
    }

    return 0;
}
