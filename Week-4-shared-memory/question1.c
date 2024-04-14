// Implementing a variable shared between a child process and its parent process
// QUESTION : below
/*Let there be a (parent) process which goes on putting a random (integer) number  in a shared variable, say n,  in a regular interval. There is a child process that goes on putting the factorial of the integer (that it finds in n) back into the shared variable (n), in regular intervals. The parent process prints the factorial that it receives from the child process. Device your own mechanism(s) so that the child process "knows" that a new number has been put in n  by the parent process and the parent process "knows" that a the factorial of a number has been put in n  by the child  process,*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int shmid;

typedef void (*sighandler_t)(int);

void releaseSHM(int signum) {
    int status;

    status = shmctl(shmid, IPC_RMID, NULL);
    if (status == 0) {
        fprintf(stderr, "Remove shared memory with id = %d.\n", shmid);
    } else if (status == -1) {
        fprintf(stderr, "Cannot remove shared memory with id = %d.\n", shmid);
    } else {
        fprintf(stderr, "shmctl() returned wrong value while removing shared memory with id = %d.\n", shmid);
    }

    status = kill(0, SIGKILL);
    if (status == 0) {
        fprintf(stderr, "kill successful.\n");
    } else if (status == -1) {
        perror("kill failed.\n");
        fprintf(stderr, "Cannot remove shared memory with id = %d.\n", shmid);
    } else {
        fprintf(stderr, "kill(2) returned wrong value.\n");
    }
}
// factorial function
unsigned int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int status;
    pid_t pid = 0;
    pid_t p1 = 0;

    sighandler_t shandler;

    shandler = signal(SIGINT, releaseSHM);

    shmid = shmget(IPC_PRIVATE, sizeof(int) + sizeof(int), IPC_CREAT | 0777);

    if (shmid == -1) {
        perror("shmget() failed: ");
        exit(1);
    }

    printf("shmget() returns shmid = %d.\n", shmid);

    p1 = fork();
    if (p1 == 0) { /* child process */
        int *pi_child;

        pi_child = shmat(shmid, NULL, 0);
        if (pi_child == (void *)-1) {
            perror("shmat() failed at child: ");
            exit(1);
        }

        int *isNewNumberChild = pi_child + 1;

        while (1) {
            // Wait for the parent to set isNewNumber to 1
            while (!*isNewNumberChild) {
                usleep(10000);  // Sleep for a short time to avoid busy-waiting
            }

            // Calculate factorial and update shared variable
            pi_child[0] = factorial(pi_child[0]);
            *isNewNumberChild = 0;
        }
        exit(0);

    } else { /* parent process */
        int *pi_parent;

        pi_parent = shmat(shmid, NULL, 0);
        if (pi_parent == (void *)-1) {
            perror("shmat() failed at parent: ");
            exit(1);
        }

        int *isNewNumberParent = pi_parent + 1;

        while (1) {
            // Generate a random number and put it in shared variable
            pi_parent[0] = rand() % 10 + 1;
            *isNewNumberParent = 1;

            // Wait for the child to finish calculating the factorial
            waitpid(p1, &status, 0);

            // Print the factorial received from the child
            printf("Parent: Received factorial = %d\n", pi_parent[0]);

            // Sleep for a while before generating the next random number
            sleep(1);
        }
        pid = wait(&status);
        printf("pid = %d status = %d!\n", pid, status);
        exit(0);
    }
}
