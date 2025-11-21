#include <stdbool.h>
#include <stddef.h>

typedef struct Queue
{
    int size;
    int f;
    int r;
    int *arr;
} queue_t;

void dequeue(queue_t *);
void enqueue(queue_t *, int value);
void free_q(queue_t *);
queue_t *get_q(size_t capacity);
bool is_empty(queue_t *);
bool is_full(queue_t *);
void peek(queue_t *, size_t pos);
void print_q(queue_t *);
