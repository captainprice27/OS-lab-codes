#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define QUEUE_SIZE 10

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
    sem_t mutex, full, empty;
} CircularQueue;

int main() {
    int shm_fd;
    CircularQueue *queue;

    // Open shared memory
    shm_fd = shm_open("/shared_memory", O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Map shared memory object
    queue = mmap(NULL, sizeof(CircularQueue), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (queue == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Consumer logic
    while (1) {
        sem_wait(&queue->full);
        sem_wait(&queue->mutex);

        // Consume item from the queue
        int item = queue->items[queue->front];
        queue->front = (queue->front + 1) % QUEUE_SIZE;
        printf("Consumed: %d\n", item);

        sem_post(&queue->mutex);
        sem_post(&queue->empty);
    }

    // Unmap shared memory
    munmap(queue, sizeof(CircularQueue));

    // Close shared memory
    close(shm_fd);

    return 0;
}
