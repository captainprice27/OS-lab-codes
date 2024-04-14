fork() creates a child process that executes the same program as its parent process does.

In today's assignments, you have to write programs where the child processes would subsequently execute some other program using execve(2) system call [see the manual by the command "man 2 execve"].

Please note that often in programs we use exec(3) family of functions [execl(), execlp(), execle(), execv(), execvp(), execvpe(), etc] for this purpose. These functions are front-ends for execve(2) system call. Manual page(s) for these functions can be viewed by the command "man 3 exec."

SYNOPSIS :<h2> **execve()** </h2> 
       #include <unistd.h>

     int execve(const char *pathname, char *const argv[],
                  char *const envp[]);

DESCRIPTION
       execve() executes the program referred to by pathname.  This causes the program that is currently being run by
       the calling process to be replaced with a new program, with newly initialized stack,  heap,  and  (initialized
       and uninitialized) data segments. Pathname must be either a binary executable

***********************************************************************************************************************************************
SYNOPSIS : <h2> **waitpid()** </h2> and all ...    
       #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *wstatus);

       pid_t waitpid(pid_t pid, int *wstatus, int options);

       int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
                       /* This is the glibc and POSIX interface; see
                          NOTES for information on the raw system call. */


DESCRIPTION
       All of these system calls are used to wait for state changes in a child of the calling process, and obtain in‐
       formation about the child whose state has changed.  A state change is considered to be: the child  terminated;
       the  child  was stopped by a signal; or the child was resumed by a signal.  In the case of a terminated child,
       performing a wait allows the system to release the resources associated with the child; if a wait is not  per‐
       formed, then the terminated child remains in a "zombie" state (see NOTES below).   
       If a child has already changed state, then these calls return immediately.  Otherwise, they block until either
       a child changes state or a signal handler interrupts the call (assuming that system calls  are  not  automati‐
       cally  restarted  using  the  SA_RESTART  flag of sigaction(2)).  In the remainder of this page, a child whose
       state has changed and which has not yet been waited upon by one of these system calls is termed waitable.

*********************************************************************************************************************
SYNOPSIS : <h2>**strtok()** </h2>    
       #include <string.h>
       
       char *strtok(char *str, const char *delim);
DESCRIPTION
       The  strtok()  function breaks a string into a sequence of zero or more nonempty tokens.  On the first call to
       strtok(), the string to be parsed should be specified in str.  In each subsequent call that should  parse  the
       same string, str must be NULL.
       The  delim  argument  specifies  a  set of bytes that delimit the tokens in the parsed string.  The caller may
       specify different strings in delim in successive calls that parse the same string.
       Each call to strtok() returns a pointer to a null-terminated string containing the next  token.   This  string
       does not include the delimiting byte.  If no more tokens are found, strtok() returns NULL.
