Under the present assignment, two programs, say, **teacher.c** and **student.c** have to be written which will be compiled into two executable files, say, teacher.out and student.out, respectively.

*At any point time, only one process will run the executable file teacher.out. However, there can be multiple (say, n number of) processes running student.out.*

That is, **there could be only one  teacher process (executing teacher.out)**  and **n number of student processes (running student.out).**

All these processes run independently, that is, the programs are executed from different terminals.

The teacher process is initiated by the command "./teacher.out",  and creates a  shared structure of type "struct QnA"  (defined below)  (say, struct QnA qa1  or struct QnA  *qap1) which is shared by all n student processes.
```
struct  QnA {

     char q100];  /* Stores the question set by the teacher process */

     char a[1000] /* Stores the answer to the question "given" by a student process */

     int roll; /* The roll number of the student who answered the question */

     time_t tm; /* To keep the time when the student answered the question.

                           Read the manual for time(), that is, "man 2 time".

                          Also see the manual entries mentioned in the "see also" section of that manual page! */

     int status; /* status = 0 means that at present there is no meaningful data in this structure.

                         status = 1 means that the teacher process has set the question in the q[ ] field and no student process has started answering it. This  (setting status to 1) is done  by the teacher process.
                         status = 2 means that one student process has started answering the question available in q[ ]. This is set by one of the student processes.


                         status = 3 means that one student process has put an answer in the a[ ] field, and "filled up" tm and roll fields appropriately. This is set by one of the student processes.
*/

}
```

The teacher process allocates the shared memory segment for qa1 structure and initializes its status field to 0. It then puts a "question" in q[ ] field, The teacher process then, in an infinite loop, "receives answers" from the student processes. 

In every iteration of this infinite loop, the teacher process (i) makes the status field to be 1 (so that, a child process can attempt the "question") and (ii) waits for a child process to make it 3 (signifying that a child process has "answered" the question). (iii) Upon getting status = 3, the parent process prints the "answer" available in a[ ] along with the roll number of the student making the answer and the time of answering.

A student process, on the other hand after attaching the qa1 shared structure,    
(i) waits for its status field to become 1 (that is, the question is available for answering).    
(ii) Upon finding status = 1, it makes status = 2, and     
(iii) puts an "answer" in a[ ] field and fills up roll and tm fields appropriately.      
(iv) The child process then makes status = 3 and terminates.

The output of the parent process should be in a readable format (like "January 31, 2024, 11:50: Roll Number 2021CSB052 answered 'Absurd Question' ")

Please remember that there will be two different programs, namely, teacher.c and student.c which are to be executed to create the teacher process and the student processes. These programs are to be executed independently from different terminals.

The teacher process, when terminated by Ctrl+C key presses, should release the shared memory that has been created during execution.

An enhancement of your program (not to be submitted today) you may try to support the following in your program.

The teacher process may keep track of the details of the student processes that gave "answers" (for example, for every "answer" what was the corresponding student process id, the owner of that student process, and anything else you may conceive).
Modify your program by changing the call to the function ftok()  to ...ftok(".", ...) and justify the outcome.
