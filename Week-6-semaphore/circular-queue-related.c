// # queue using array related functions .........


#include <stdio.h>
#define MAX_SIZE 100

// Structure to represent the queue
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Function to initialize the queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Function to check if the queue is full
int isFull(Queue *q) {
    return (q->rear == MAX_SIZE - 1);
}

// Function to add an element to the queue
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full, cannot enqueue.\n");
        return;
    } else if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->items[q->rear] = value;
}

// Function to remove an element from the queue
int dequeue(Queue *q) {
    int deletedItem;
    if (isEmpty(q)) {
        printf("Queue is empty, cannot dequeue.\n");
        return -1; // Return some default value indicating failure
    } else if (q->front == q->rear) {
        deletedItem = q->items[q->front];
        q->front = q->rear = -1;
    } else {
        deletedItem = q->items[q->front];
        q->front++;
    }
    return deletedItem;
}

// Function to display the elements in the queue
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    displayQueue(&q);
    printf("Dequeued item: %d\n", dequeue(&q));
    displayQueue(&q);
    return 0;
}



// *******************************************************************************

# circular queue using array related functions


#include <stdio.h>
#define MAX_SIZE 100

// Structure to represent the circular queue
typedef struct {
    int items[MAX_SIZE];
    int front, rear;
    int size;
} CircularQueue;

// Function to initialize the circular queue
void initCircularQueue(CircularQueue *cq) {
    cq->front = -1;
    cq->rear = -1;
    cq->size = 0;
}

// Function to check if the circular queue is empty
int isCircularQueueEmpty(CircularQueue *cq) {
    return (cq->size == 0);
}

// Function to check if the circular queue is full
int isCircularQueueFull(CircularQueue *cq) {
    return (cq->size == MAX_SIZE);
}

// Function to add an element to the circular queue
void enqueueCircularQueue(CircularQueue *cq, int value) {
    if (isCircularQueueFull(cq)) {
        printf("Circular queue is full, cannot enqueue.\n");
        return;
    }
    if (cq->front == -1)
        cq->front = 0;
    cq->rear = (cq->rear + 1) % MAX_SIZE;
    cq->items[cq->rear] = value;
    cq->size++;
}

// Function to remove an element from the circular queue
int dequeueCircularQueue(CircularQueue *cq) {
    int deletedItem;
    if (isCircularQueueEmpty(cq)) {
        printf("Circular queue is empty, cannot dequeue.\n");
        return -1; // Return some default value indicating failure
    }
    deletedItem = cq->items[cq->front];
    if (cq->front == cq->rear)
        cq->front = cq->rear = -1;
    else
        cq->front = (cq->front + 1) % MAX_SIZE;
    cq->size--;
    return deletedItem;
}

// Function to display the elements in the circular queue
void displayCircularQueue(CircularQueue *cq) {
    int i;
    if (isCircularQueueEmpty(cq)) {
        printf("Circular queue is empty.\n");
        return;
    }
    printf("Circular queue elements: ");
    for (i = cq->front; i != cq->rear; i = (i + 1) % MAX_SIZE)
        printf("%d ", cq->items[i]);
    printf("%d\n", cq->items[i]);
}

int main() {
    CircularQueue cq;
    initCircularQueue(&cq);
    enqueueCircularQueue(&cq, 10);
    enqueueCircularQueue(&cq, 20);
    enqueueCircularQueue(&cq, 30);
    displayCircularQueue(&cq);
    printf("Dequeued item: %d\n", dequeueCircularQueue(&cq));
    displayCircularQueue(&cq);
    return 0;
}


