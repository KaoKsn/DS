// 5. Circular queues using dynamic arrays.
typedef struct Queue {
    int *arr;
    int front;
    int rear;
    int size;
} q_t;

#include <stdio.h>
#include <stdlib.h>
#define FAILURE 1

q_t *getQ(int);
void insert(q_t *q, int);
int delete(q_t *q);
void printQ(q_t *q);
void freeQ(q_t *q);


int main() {
    int choice, value;

    q_t *q = getQ(2);
    while (1) {
        printf("\n--- Queue MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                insert(q, value);
                break;
            case 2:
                delete(q);
                break;
            case 3:
                printQ(q);
                break;
            case 4:
                printf("Exiting...\n");
                freeQ(q);
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

q_t *getQ(int capacity) {
    q_t *q = malloc(sizeof(q_t));
    if (q == NULL)
        return NULL;
    q->arr = calloc(capacity, sizeof(int));
    if (q->arr == NULL) {
        free(q);
        return NULL;
    }
    q->front = q->rear = 0;
    q->size = capacity;
    return q;
}

void insert(q_t *q, int value)
{
    if (q == NULL) {
        return;
    }
    // If the queue is full.
    if (q->front == (q->rear + 1) % q->size) {
        // Resize the queue.
        int *tmp = malloc(sizeof(int) * q->size * 2);
        if (tmp == NULL) {
            printf("Couldn't resize. Insertion Aborted!\n");    
            return;
        }
        int index = 0;
        for (int i = q->front; i != q->rear; i = (i + 1) % q->size)
            tmp[index++] = q->arr[i];
        free(q->arr);
        q->arr = tmp;

        // Set the new rear, front and capacity.
        q->front = 0;
        q->size *= 2;
        q->rear = index;
    }
    // Finally insert.
    q->arr[q->rear] = value;
    q->rear = (q->rear + 1) % q->size;
}

int delete(q_t *q)
{
    if (q == NULL || q->front == q->rear) {
        printf("Empty!\n");
        return FAILURE;
    } 
    int returnVal = q->arr[q->front];
    q->front = (q->front+1) % q->size;
    printf("%d\n", returnVal);
    return returnVal;
}

void printQ(q_t *q)
{
    if (q == NULL || q->front == q->rear)
        return;
    printf("=== Queue ===\n");
    printf("front -->\t");
    for (int i = q->front; i != q->rear; i = (i + 1) % q->size)
        printf("%d\t", q->arr[i]);
    printf("<-- rear\n");
}

void freeQ(q_t *q)
{
    if (q == NULL || q->arr == NULL)
        return;
    free(q->arr);
    free(q);
}
