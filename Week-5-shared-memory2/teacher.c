#include <stdio.h>
#include <stdlib.h> // for malloc , free , exit etc ...
#include <string.h> // for string related fns
#include <sys/shm.h>    // for sharedd mem related fns like shmget() , shmctl() etc
#include <sys/ipc.h>    // for inter process communication (IPC)
#include <sys/types.h>  // for pid_t process id etc ...
#include <unistd.h> // for fork() function
#include <time.h>   // for time() etc ...
#include <signal.h> // for signal handler

// Shared structure definition
struct QnA
{
    char q[100];
    char a[1000];
    int roll;       //simple int roll form (not 2021CSBxxx type)
    time_t tm;  /// // whichnis of integer type
    int status; // 0: No data, 1: Question set, 2: Student answering, 3: Answer received as of question
};

// Signal handler to release shared memory on Ctrl+C
// copy pasted from precv code ...
void sigintHandler(int signum)
{
    printf("\nTerminating teacher process. Releasing shared memory.\n");
    // Detach and remove shared memory
    if (shmctl(shm_id, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
    }
    exit(0);
}

int main()
{
    key_t key = ftok(".", 'S');
    int shm_id = shmget(key, sizeof(struct QnA), IPC_CREAT | 0666);
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

    // Set up signal handler for Ctrl+C
    signal(SIGINT, sigintHandler);


    // Initialize shared structure
    memset(qa1->q, 0, sizeof(qa1->q));
    memset(qa1->a, 0, sizeof(qa1->a));
    qa1->roll = 0;
    qa1->tm = 0;
    qa1->status = 0;

    while (1)
    {
        // Set status to 1 (question available)
        printf("what is 2+2 ?");
        qa1->status = 1;

        // Wait for a student to answer (status = 3)
        while (qa1->status != 3)
            ;

        // Print the answer received
        printf("%s: Roll Number %d answered '%s'\n", ctime(&qa1->tm), qa1->roll, qa1->a);

        // Clear the answer fields
        memset(qa1->a, 0, sizeof(qa1->a));
        qa1->roll = 0;
        qa1->tm = 0;

        // Set status back to 0 (no data)
        qa1->status = 0;
    }

    return 0;
}
