#include <stdbool.h>

int size = 0;

// A stack node.
typedef struct Stack_node
{
  int number;
  struct Stack_node *next;
} stack_node_t;

// Functions.
stack_node_t *create_stack(int capacity);
void free_stack(stack_node_t *stack);
stack_node_t pop(stack_node_t **stack);
void print_stack(stack_node_t *stack);
bool push(stack_node_t **stack, int value);
