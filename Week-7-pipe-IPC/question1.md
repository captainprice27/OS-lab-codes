## A simple assignment on pipe (the IPC tool) - communication between parent and its child process using "pipe"

Let there be a C structure as defined below for storing student information.

struct student 
{   
         int roll;   
         char name[100];   
}   

There are 2 processes, P1 and P2 (parent and child process, respectively), where P1 fills up an array "struct student ss[100]" with information (roll number and name) of n students (value of n to be taken as input) from the user and sends those structures to its child process P2 over a pipe (the IPC tool).

P2, on the other hand, reads those n structures, stores them in an array, sorts them in ascending order of "roll" and sends those sorted structures back to P1 over another pipe.

P1, finally, prints the contents of the structures in user-readable format.
