#include <stdio.h>
#include <stdlib.h>    // for malloc , free , exit etc ...
#include <string.h>    // for string related fns
#include <sys/shm.h>   // for sharedd mem related fns like shmget() etc
#include <sys/ipc.h>   // for inteer process communication
#include <sys/types.h> // for pid_t process id etc ..
#include <unistd.h>    // for fork() function and sleep() function
#include <time.h>      // for time() etc ...
#include <signal.h>    // for signal handler

// THOUGH WE DON'T NEED SIGNAL HANDLER FOR STUDENT CODE ...

// Shared structure definition
struct QnA
{
    char q[100];    // question string
    char a[1000];   // answer string
    int roll;   // simple int roll form (not 2021CSBxxx type)
    time_t tm;  // whichnis of integer type
    int status; // 0: No data, 1: Question set, 2: Student answering, 3: Answer received as of the question given
};

int main()
{
    key_t key = ftok(".", 'S');
    int shm_id = shmget(key, sizeof(struct QnA), 0666);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    struct QnA *qa1 = (struct QnA *)shmat(shm_id, NULL, 0);
    if (qa1 == (struct QnA *)(-1))
    {
        perror("shmat");
        exit(1);
    }

    while (1)
    {
        // Wait for the question(status = 1)
        while (qa1->status != 1)
            ;

        // student answering the question
        qa1->status = 2;

        // student answer
        strcpy(qa1->a, "answer to the question is 4");
        qa1->roll = 71;
        qa1->tm = time(NULL);

        // answer received by teacher
        qa1->status = 3;

        // Sleep for 2 sec , which is between time
        sleep(2);
    }

    return 0;
}
