// implemetation of a primitive shell
// supports cd , mkdir , exit , pwd , exit ...

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

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

    while (1)
    {
        printf("mysh> ");   // mysh shell indicator

        // Read command from stdin
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break; // Exit on EOF
        }

        // Parse command into tokens
        token = strtok(command, delimiters);
        // string --> tokens
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, delimiters);
        }
        args[i] = NULL;

        // Handle internal commands
        if (args[0] != NULL)
        {
            handle_internal_command(args);
        }

        // Fork and execute external commands
        /// external command will be handled by child process  
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            if (execvp(args[0], args) < 0)  // int execvp(const char *file, char *const argv[]);
            {
                perror("execvp");
                exit(1);
            }
        }
        else
        {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
