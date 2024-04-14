#include <stdio.h>
#include <unistd.h> // for fork()
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define MAX_SIZE 100

int shmid;

void releaseSHM(int signum)
{
    int status;

    status = shmctl(shmid, IPC_RMID, NULL);
    if (status == 0)
    {
        fprintf(stderr, "Remove shared memory with id = %d.\n", shmid);
    }
    else
    {
        fprintf(stderr, "Cannot remove shared memory with id = %d.\n", shmid);
    }

    exit(signum);
}

void computeRow(int row, int n, int m, int q, int *a, int *b, int *c)
{
    int sum;

    for (int j = 0; j < q; j++)
    {
        sum = 0;
        for (int k = 0; k < m; k++)
        {
            sum += a[row * m + k] * b[k * q + j];
        }
        c[row * q + j] = sum;
    }
}

int main()
{
    int n, m, p, q;
    int a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE], c[MAX_SIZE][MAX_SIZE];

    printf("Enter the number of rows (n) for matrix A: ");
    scanf("%d", &n);
    printf("Enter the number of columns (m) for matrix A: ");
    scanf("%d", &m);

    printf("Enter the number of rows (p) for matrix B: ");
    scanf("%d", &p);
    printf("Enter the number of columns (q) for matrix B: ");
    scanf("%d", &q);

    if (m != p)
    {
        printf("Error: The number of columns in matrix A must be equal to the number of rows in matrix B.\n");
        return 1;
    }

    // Create shared memory for matrices
    shmid = shmget(IPC_PRIVATE, sizeof(int) * n * m + sizeof(int) * m * q + sizeof(int) * n * q, IPC_CREAT | 0777);
    if (shmid == -1)
    {
        perror("shmget() failed: ");
        return 1;
    }

    printf("Shared memory segment ID: %d\n", shmid);

    // Attach shared memory to arrays
    int *a_shared = (int *)shmat(shmid, NULL, 0);
    int *b_shared = a_shared + n * m;
    int *c_shared = b_shared + m * q;

    printf("Enter elements for matrix A:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
            a_shared[i * m + j] = a[i][j];
        }
    }

    printf("Enter elements for matrix B:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &b[i][j]);
            b_shared[i * q + j] = b[i][j];
        }
    }

    // Fork n child processes
    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Fork failed");
            releaseSHM(1);
        }
        else if (pid == 0)
        {
            // Child process computes its row
            computeRow(i, n, m, q, a_shared, b_shared, c_shared);
            exit(0);
        }
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < n; i++)
    {
        wait(NULL);
    }

    // Print the resulting matrix C
    printf("Resulting Matrix C:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < q; j++)
        {
            printf("%d ", c_shared[i * q + j]);
        }
        printf("\n");
    }

    // Detach and release shared memory
    shmdt(a_shared);
    releaseSHM(0);

    return 0;
}
