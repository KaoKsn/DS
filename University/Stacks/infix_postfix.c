#include "infix_postfix.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{ 
  char *infix = "a+b*c-d/e";

  printf("Infix: %s\n", infix);

  // Convert infix to postfix.
  char *postfix = topostfix(infix);

  printf("Postfix: %s\n", postfix);

  free(postfix);
  return 0;
}

// Convert infix expression to postfix expression.
char *topostfix(char *infix)
{
  int len = strlen(infix);
  char *postfix = calloc(len + 1, sizeof(char));
  if (postfix == NULL)
  {
    fprintf(stderr, "Failed Memory Allocation!\n");
    return NULL;
  }
 
  // Getting the stack. 
  stack_t *stack = get_stack(strlen(infix)+1);
  if (stack == NULL)
  {
    fprintf(stderr, "Failed Memory Allocation!\n");
    return NULL;
  }

  int index = 0;
  // Travel through the infix expression and perform stack operations.
  for (int i = 0; infix[i] != '\0'; i++)
  {
    // Send variables as is.
    if (isalpha(infix[i]) || isdigit(infix[i]))
    {
      postfix[index++] = infix[i];
    }
    else
    {
      // Directly push to the stack, if a higher precedence operator is scanned. 
      if (!isempty(stack))
      {
        if (precedence(infix[i]) > precedence(stack->expression[stack->top]))
        {
          push(stack, infix[i]);
        }
        else
        {
          // Pop untill, the current infix operator's precedence is greater than the one in the stack.
          while (!isempty(stack) && precedence(infix[i]) <= precedence(stack->expression[stack->top]))
            postfix[index++] = pop(stack);
          // Push the current element to stack.
          push(stack, infix[i]);
        }
      }
      else
      {
        push(stack, infix[i]);
      }
    }
  }
  // Directly use any remaining elements in the stack.
  while (!isempty(stack))
  {
    postfix[index++] = pop(stack);
  }

  free(stack->expression);
  free(stack);
  return postfix;
}

int precedence(char operator)
{
  if (operator == '*' || operator == '/')
  {
    return 2;
  }
  else
  {
    return 1;
  }
}

// Create a stack.
stack_t *get_stack(int len)
{
  stack_t *stack = malloc(sizeof(stack_t));
  if (stack == NULL)
  {
    fprintf(stderr, "Mem Allocation Failed!\n");
    return NULL;
  }

  stack->top = -1;
  stack->size = len;
  stack->expression = calloc(len + 1, sizeof(char));
  if (stack->expression == NULL)
  {
    fprintf(stderr, "Memory Allocation Failed!\n");
    return NULL;
  }
  stack->expression[len] = '\0';
  return stack;
}

// Push and increment top counter.
void push(stack_t *stack, char value)
{
  if (stack == NULL)
  {
    return;
  }
  if (isfull(stack))
  {
    fprintf(stderr, "Stack Full!\n");
    return;
  }
  stack->expression[++(stack->top)] = value;
}

// Pop the top element.
char pop(stack_t *stack)
{
  if (stack == NULL)
  {
    return '\0';
  }

  if (isempty(stack))
  {
    fprintf(stderr, "Stack Empty!\n");
    return '\0';
  }
  return stack->expression[(stack->top)--];
}

// Checks if the stack is full.
bool isfull(stack_t *stack)
{
  if (stack->top == stack->size - 1)
  {
    return true;
  }
  return false;
}

// Checks if the stack is empty.

bool isempty(stack_t *stack)
{
  if (stack->top == -1)
  {
    return true;
  }
  return false;
}
