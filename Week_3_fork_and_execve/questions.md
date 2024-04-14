Write a C program which, in every iteration of an infinite-loop, reads the name of an executable file and creates a child process to execute it. The execution of the program is to be terminated by pressing ^C (Ctrl+C keys pressed together).

Write the program in the following steps.

Your Program File Name: **forkNexec1.c** : This program, in one infinite loop just reads a string (supposed to be an executable file name in later steps) and prints it. Naturally, the execution of the program is to be terminated by pressing ^C (Ctrl+C keys pressed together).

Your Program File Name: **forkNexec2.c** : Modify the program (in file forkNexec1.c) of the previous step, so that in every iteration of the infinite loop, after reading the string, it creates a child process that just prints the string (which has been read by its parent process). The parent process should wait for the termination of the child process before resuming the next iteration of the infinite-loop. Here too, the execution of the program is to be terminated by pressing ^C.

 Your Program File Name: **forkNexec3.c** : Modify the program (in file forkNexec2.c) of the previous step, so that, now the child process, in place of printing the string, executes a file named by that string. Now too, the parent process waits for the termination of the child process before resuming the next iteration of the infinite-loop. The parent process should report whether the  child process (which is now executing some arbitrary executable file) has terminated normally or abnormally. Parent should print as much detailed reporting as possible. 
 
Explore what happens when in place of executable files the user provides (i) a C program file (ii) a  directory (iii) a non-existent file (name), etc.,  for execution.
Write your observation and justification for this in the text-area available in the submission page.

Please note the files executed by the child processes could be your files (like, a1.out, a2.out, etc.)  or executable files available in the system (like, /bin/ls, /bin/ps, /bin/cp, etc.)
