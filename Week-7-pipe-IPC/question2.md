## This is an extension of the previous assignment.

Let there be a C structure as defined below for storing student information.

struct student 
{
         int roll;
         char name[100];
         void *data_p;
         int data_size;
}

The roll and name fields store the roll number and name of a student as in the original assignment. The pointer field data_p points to data_size (the 4th field of the structure) number of bytes, that stores some information about the student (you decide what additional information to keep in this field. Please note that memory space has to be allocated (by malloc, caloc, alloc, ...) for storing this additional information, and data_p will just point to that allocated space, whereas, data_size will hold the size (that is, the number of bytes) of that space.

There are 2 processes, P1 and P2 (parent and child process, respectively), where P1 fills up an array "struct student ss[100]" with information (roll number, name, and some other information (you decide what information to keep) pointed to by data_p) of n students (value of n to be taken as input) from the user and sends those structures to its child process P2 over a pipe (the IPC tool).

P2, on the other hand, reads those n structures, stores them in an array, sorts them in ascending order of "roll" and sends those sorted structures back to P1 over another pipe.

P1, finally, prints the contents of the structures in user-readable format.
