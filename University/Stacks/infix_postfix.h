#include <stdbool.h>
typedef struct Stack
{
  int top;
  int size;
  char *expression;
} stack_t;

stack_t *get_stack(int);
bool isempty(stack_t *stack);
bool isfull(stack_t *stack);
char pop(stack_t *stack);
int precedence(char);
void push(stack_t *stack, char value);
char *topostfix(char *);

