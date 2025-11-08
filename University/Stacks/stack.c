// Stack implementation using singly-linked-lists.
#include<stdio.h>
#include<stdlib.h>

typedef struct stack_element{
  int number;
  struct stack_element *next;
}stack_element;

int stack_size = 0;

stack_element *create_stack();
void insert_element(stack_element **stack);
void delete_element(stack_element **stack);
void print_stack(stack_element *stack);
void free_stack(stack_element *stack);

stack_element *create_stack(){
  stack_element *stack = NULL;

  int total_elements;

  // Read the number of elements in the stack.
  printf("Number of elements for stack initialization: ");
  scanf("%d", &total_elements);
 
  // Building a reversed linked-list to follow the last-in-first-out principle.
  for(int i = 0; i < total_elements; i++){
    stack_element *node = (stack_element *)malloc(sizeof(stack_element));
    
    if (node == NULL){
      // If the stack itself is empty, quit stack initialization for now.
      if (stack == NULL){
        fprintf(stderr, "Stack initialization failed!\n");
        break;
      }
      // Stop reading elements to the stack if memory allocation for a block fails.
      else{
        fprintf(stderr, "Stack element insertion stopped due to failed memory allocation\n");
        break;
      }
    }

    // On successful allocation, insert the element into the stack.
    printf("Number: ");
    scanf("%d", &(node->number));
    

    // If it's the first element of the stack insert it.
    if (stack == NULL){
      stack = node;
      node->next = NULL;
    }
    else{
      node->next = stack;
      stack = node;
    }
    stack_size++;
  }

  return stack;
}

// Inserting an element into the stack.
void insert_element(stack_element **stack){
  stack_element *node = (stack_element *)malloc(sizeof(stack_element));
  
  printf("\n+++ Insertion +++\n");
  if (node == NULL){
      fprintf(stderr, "\nInsertion Failed!\n");
      return;
  }

  // On successful allocation, insert the element into the stack.
  printf("Number: ");
  scanf("%d", &(node->number));

  // If it's the first element of the stack insert it directly.
  if (*stack == NULL){
    *stack = node;
    node->next = NULL;
  }

  // Insert the element to form a reversed linked-list.
  else{
    node->next = *stack;
    *stack = node;
  }
  stack_size++;

  return;
}

// Deletion of the top element from the stack.
void delete_element(stack_element **stack){

  printf("\n--- Deletion ---\n");
  stack_element *tmp = *stack;
  // Change the value of top to top-1.
  *stack = (*stack)->next;

  free(tmp);

  stack_size--;
  return;
}

// Printing the stack.
void print_stack(stack_element *stack){
  printf("\n=== Stack ===\n");
  while (stack != NULL){
    printf("%d\n", stack->number);
    stack = stack->next;
  }
  return;
}

// Freeing the dynamically allocated memory to the stack.
void free_stack(stack_element *stack){
  for(stack_element *ptr = stack; ptr != NULL;){

    stack_element *tmp = ptr->next;
    free(ptr);

    ptr = tmp;
  }
  return;
}
