fork() creates a child process that executes the same program as its parent process does.

In today's assignments, you have to write programs where the child processes would subsequently execute some other program using execve(2) system call [see the manual by the command "man 2 execve"].

Please note that often in programs we use exec(3) family of functions [execl(), execlp(), execle(), execv(), execvp(), execvpe(), etc] for this purpose. These functions are front-ends for execve(2) system call. Manual page(s) for these functions can be viewed by the command "man 3 exec."

SYNOPSIS
       #include <unistd.h>

     int execve(const char *pathname, char *const argv[],
                  char *const envp[]);

DESCRIPTION
       execve() executes the program referred to by pathname.  This causes the program that is currently being run by
       the calling process to be replaced with a new program, with newly initialized stack,  heap,  and  (initialized
       and uninitialized) data segments. Pathname must be either a binary executable
