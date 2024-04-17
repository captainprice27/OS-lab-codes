#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>

#define QUEUE_SIZE 10
#define MAX_ITEMS_PER_PRODUCER 10

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
    sem_t mutex, full, empty;
} CircularQueue;

void produce(CircularQueue *queue, int num_items) {
    for (int i = 0; i < num_items; i++) {
        printf("Producer produced item %d\n", i + 1);
        sem_wait(&queue->empty);
        sem_wait(&queue->mutex);
        // Add item to the queue
        queue->items[queue->rear] = i + 1;
        queue->rear = (queue->rear + 1) % QUEUE_SIZE;
        sem_post(&queue->mutex);
        sem_post(&queue->full);
    }
}

int main() {
    int shm_fd;
    CircularQueue *queue;

    // Create or open shared memory
    shm_fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Configure the size of the shared memory segment
    if (ftruncate(shm_fd, sizeof(CircularQueue)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Map shared memory object
    queue = mmap(NULL, sizeof(CircularQueue), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (queue == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphore
    sem_init(&queue->mutex, 1, 1);
    sem_init(&queue->full, 1, 0);
    sem_init(&queue->empty, 1, QUEUE_SIZE);

    // Producer logic
    while (1) {
        int num_items;
        printf("Enter the number of items to produce (1-%d, 0 to exit): ", MAX_ITEMS_PER_PRODUCER);
        scanf("%d", &num_items);
        if (num_items == 0)
            break;
        if (num_items < 1 || num_items > MAX_ITEMS_PER_PRODUCER) {
            printf("Invalid input. Please enter a number between 1 and %d.\n", MAX_ITEMS_PER_PRODUCER);
            continue;
        }
        produce(queue, num_items);
    }

    // Unmap shared memory
    munmap(queue, sizeof(CircularQueue));

    // Close shared memory
    close(shm_fd);

    return 0;
}
