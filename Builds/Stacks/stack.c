// Stack implementation using singly-linked-lists.
#include "stack.h"

#include<stdio.h>
#include<stdlib.h>


int main(void)
{
  int capacity = 10;

  stack_node_t *stack = create_stack(capacity);
  printf("Current length of the stack: %d\n", size);

  if (push(&stack, 3) == true)
  {
    printf("Length after insertion into the stack: %d\n", size);
  }

  stack_node_t popped = pop(&stack);
  printf("Value Popped: %d\n", popped.number);
  printf("Length after deletion from the stack: %d\n", size);

  print_stack(stack);

  free_stack(stack);
  return 0;
}

stack_node_t *create_stack(int capacity)
{
  stack_node_t *stack = NULL;

  // Building a reversed linked-list to follow the last-in-first-out principle.
  for(int i = 0; i < capacity; i++)
  {
    stack_node_t *node = malloc(sizeof(stack_node_t));
    
    if (node == NULL)
    {
      // If the stack itself is empty, quit stack initialization for now.
      if (stack == NULL)
      {
        fprintf(stderr, "Stack initialization failed!\n");
        break;
      }
      // Stop reading elements to the stack if memory allocation for a block fails.
      else
      {
        fprintf(stderr, "Stack element insertion stopped due to failed memory allocation\n");
        break;
      }
    }

    // On successful allocation, insert the element into the stack.
    printf("Number: ");
    scanf("%d", &(node->number));
    
    // If it's the first element of the stack directly insert it.
    if (stack == NULL)
    {
      stack = node;
      node->next = NULL;
    }
    else
    {
      node->next = stack;
      stack = node;
    }
    size++;
  }
  return stack;
}

// Inserting an element into the stack.
bool push(stack_node_t **stack, int value)
{
  stack_node_t *node = malloc(sizeof(stack_node_t));
  
  printf("\n+++ Insertion +++\n");
  if (node == NULL)
  {
      fprintf(stderr, "\nInsertion Failed!\n");
      return false;
  }

  // On successful allocation, insert the element into the stack.
  node->number = value;

  // If it's the first element of the stack insert it directly.
  if (*stack == NULL)
  {
    *stack = node;
    node->next = NULL;
  }

  // Insert the element to form a reversed linked-list.
  else
  {
    node->next = *stack;
    *stack = node;
  }
  size++;

  return true;
}

// Deletion of the top element from the stack.
stack_node_t pop(stack_node_t **stack)
{
  printf("\n--- Deletion ---\n");
  stack_node_t *tmp = *stack;
  // Change the value of top to top-1.
  *stack = (*stack)->next;

  stack_node_t popped = *tmp;

  free(tmp);
  size--;
  return popped;
}

// Printing the stack.
void print_stack(stack_node_t *stack)
{
  printf("\n=== Stack ===\n");
  while (stack != NULL)
  {
    printf("%d\n", stack->number);
    stack = stack->next;
  }
  return;
}

// Freeing the dynamically allocated memory to the stack.
void free_stack(stack_node_t *stack){
  for(stack_node_t *ptr = stack; ptr != NULL;)
  {
    stack_node_t *tmp = ptr->next;
    free(ptr);

    ptr = tmp;
  }
  return;
}
