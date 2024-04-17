#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define QUEUE_SIZE 10
#define MAX_ITEMS_PER_CONSUMER 10

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
    sem_t mutex, full, empty;
} CircularQueue;

void consume(CircularQueue *queue, int num_items) 
{
    for (int i = 0; i < num_items; i++) {
        sem_wait(&queue->full);
        sem_wait(&queue->mutex);
        // Consume item from the queue
        int item = queue->items[queue->front];
        queue->front = (queue->front + 1) % QUEUE_SIZE;
        printf("Consumer consumed item %d\n", item);
        sem_post(&queue->mutex);
        sem_post(&queue->empty);
    }
}

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
        int num_items;
        printf("Enter the number of items to consume (1-%d, 0 to exit): ", MAX_ITEMS_PER_CONSUMER);
        scanf("%d", &num_items);
        if (num_items == 0)
            break;
        if (num_items < 1 || num_items > MAX_ITEMS_PER_CONSUMER) {
            printf("Invalid input. Please enter a number between 1 and %d.\n", MAX_ITEMS_PER_CONSUMER);
            continue;
        }
        consume(queue, num_items);
    }

    // Unmap shared memory
    munmap(queue, sizeof(CircularQueue));

    // Close shared memory
    close(shm_fd);

    return 0;
}
