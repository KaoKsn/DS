// A simple fixed size circular queue implementation using arrays.
// The queue can only handle integer values.

// NOTE: The either the first or the last position is empty.
// front and rear inititalized to 0 to avoid overwriting of queue elements.
// front index remains empty.
// when rear = 0 and front = size - 1, top position is empty.
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_int(char *);

int main(void)
{
    queue_t *q = get_q(5);
    int choice;
    while (true) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Print Queue\n");
        printf("4. Peek\n");
        printf("5. Quit\n");
        choice = get_int("Choice");
        switch (choice) {
            case 1:
                int value = get_int("Value");
                enqueue(q, value);
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                print_q(q);
                break;
            case 4:
                int pos = get_int("Index");
                peek(q, pos);
                break;
            case 5:
                free_q(q);
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }
    return 0;
}

queue_t *get_q(size_t capacity)
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        fprintf(stderr, "Memory Allocation Failed!\n");
        return NULL;
    }
    q->arr = malloc(sizeof(int) * capacity);
    if (q->arr == NULL) {
        fprintf(stderr, "Memory Allocation Failed!\n");
        return NULL;
    }
    q->size = capacity;
    q->f = q->r = 0;
    return q;
}

// Enqueue from the front end.
void enqueue(queue_t *q, int value)
{
   if (q == NULL || q->arr == NULL) {
        fprintf(stderr, "NULL passed! Aborting enqueue\n");
        return;
    } else if (is_full(q)) {
        fprintf(stderr, "Queue Full!\n");
        return;
    }
    q->r = (q->r + 1) % q->size;
    q->arr[q->r] = value;
    return;
}

// Dequeue item from the front end.
void dequeue(queue_t *q)
{
    if (q == NULL || q->arr == NULL) {
        fprintf(stderr, "NULL passed! Aborting dequeue\n");
        return;
    } else if (is_empty(q)) {
        fprintf(stderr, "Queue Empty\n");
        return;
    }
    q->f = (q->f + 1) % q->size; 
    printf("Dequeued: %d\n", q->arr[q->f]);
    return;
}

// Check if the queue is full.
bool is_full(queue_t *q)
{
    if (q == NULL) {
        return true;
    } else if ((q->r + 1) % q->size == q->f) {
        return true;
    }
  return false;
}

// Check if the queue is empty.
bool is_empty(queue_t *q)
{
    if (q == NULL) {
        return true;
    } else if (q->f == q->r) {
        return true;
    }
  return false;
}

// Get an element from a valid index in a queue.
void peek(queue_t *q, size_t pos)
{
    if (q == NULL || q->arr == NULL) {
        return;
    } else if (is_empty(q)) {
        fprintf(stderr, "Queue Empty!\n");
        return;
    } else if (pos >= q->size || pos < 0){
        fprintf(stderr, "Invalid Index Requested!\n");
        return;
    } else if ((q->r > q->f) && (pos > q->r || pos < q->f +1)){
        fprintf(stderr, "Invalid Index Requested!\n");
        return;
    } else if (pos > q->r && pos < q->f + 1) {
        fprintf(stderr, "Invalid Index Requested!\n");
        return;
    }
    printf("Value at position %d is: %d\n", pos, q->arr[pos]);
    return;
}

// Print the queue
void print_q(queue_t *q)
{
    if (q == NULL || q->arr == NULL) {
        return;
    } else if (is_empty(q)) {
        fprintf(stderr, "Queue Empty!\n");
        return;
    }
    printf("---Queue---\n");
    for (int i = (q->f + 1) % q->size; i != q->r; i = (i + 1) % q->size) {
        printf("%d\n", q->arr[i]);
    }
    printf("%d\n", q->arr[q->r]);
}

// Free the queue.
void free_q(queue_t *q)
{
    if (q == NULL || q->arr == NULL) {
        return;
    }
    free(q->arr);
    free(q);
    q = NULL;
    return;
}

int get_int(char *str)
{
    int value;
    while (true) {
        if (str == NULL || strlen(str) == 0) {
            printf("Enter an integer: ");
        } else {
            printf("%s: ", str);
        }

        if (scanf("%d", &value) != 1) {
            int buffer;
            while (buffer = getchar() != '\n');
        } else {
            break;
        }
    }
    return value;
}
