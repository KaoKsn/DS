#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define EVAL_FAILED -255

typedef struct Stack{
  int capacity;
  int top;
  int *arr;
} stack_t;

stack_t *get_stack(size_t capacity);
bool push(stack_t *stack, size_t value);
int pop(stack_t *stack);
void free_stack(stack_t *stack);
void push_success(bool truth);
// Postfix expr evaluator.
int eval(const char *postfix);

// Definitions.
stack_t *get_stack(size_t capacity)
{
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL) {
        return NULL;
    }
    stack->arr = calloc(capacity, sizeof(int));
    if (stack->arr == NULL) {
        free(stack);
        return NULL;
    }
    stack->top = 0;
    stack->capacity = capacity;
    return stack;
}

// Inserting an element into the stack.
bool push(stack_t *stack, size_t value){
  if (stack == NULL) {
      fprintf(stderr, "Initialize a stack!\n");
      return false;
  } else if (stack->top == stack->capacity) {
      int *tmp = realloc(stack->arr, stack->capacity * 2);
      if (tmp == NULL) {
          fprintf(stderr, "Failed to expand the stack! Aborting evaluation!\n");
          exit(EVAL_FAILED);
      }
      stack->capacity *= 2;
      stack->arr = tmp;
  }
  stack->arr[(stack->top)++] = value;
  return true;
}

// Deletion of the top element from the stack.
int pop(stack_t *stack){
  if (stack == NULL) {
      fprintf(stderr, "Stack doesn't exists!\n");
      exit(EVAL_FAILED);
  }
  else if (stack->top == 0) {
      fprintf(stderr, "Stack empty!\n");
      exit(EVAL_FAILED);
  }
  return stack->arr[--(stack->top)];
}

// Freeing the dynamically allocated memory to the stack.
void free_stack(stack_t *stack){
    if (stack == NULL) {
        return;
    }
    free(stack->arr);
    free(stack);
    return;
}
