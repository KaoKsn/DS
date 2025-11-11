#include "eval_postfix.h"

#include <ctype.h>
#include <string.h>

int main(void)
{
    const char *postfix = "56+34*2-81/+*";
    int eval_result = eval(postfix);

    printf("The expression evaluates to: %d\n", eval_result);
    return 0;
}

// Evaluate the postfix expression.
int eval(const char *postfix)
{
    stack_t *stack = get_stack(10);
    if (stack == NULL) {
        fprintf(stderr, "Failed to initialize a stack!Aborting!\n");
        exit(EVAL_FAILED);
    }
    int value = 0;
    int len = strlen(postfix);

    for (int i = 0; i < len; i++) {
        // If the item is a character, push it to the stack.
        if (isdigit(postfix[i])) {
            push(stack, postfix[i] - '0');
        }
        else {
            int second = pop(stack);
            int first = pop(stack);
            int res = 0;
            switch (postfix[i]) {
                case '+' :
                      res = first + second;
                      break; 
                case '-' :
                      res = first - second;
                      break; 
                case '*' :
                      res = first * second;
                      break; 
                case '/' :
                      if (second != 0)
                          res = first / second;
                      else {
                          fprintf(stderr, "Division by 0 encountered! Aborting!\n");
                          exit(EVAL_FAILED);
                      }
                      break; 
                case '%' :
                      if (second != 0)
                          res = first % second;
                      else {
                          fprintf(stderr, "Division by 0 encountered! Aborting!\n");
                          exit(EVAL_FAILED);
                      }
                      break; 
                default:
                      fprintf(stderr, "Invalid operator encountered! Please QUIT!\n");
                      free_stack(stack);
                      exit(EVAL_FAILED);
            }
            if (push(stack, res) == false) {
                  fprintf(stderr, "Evaluation failed due to invalid operations!\n");
                  exit(EVAL_FAILED);
            }
        }
    }
    if (stack->top - 1 == 0) {
        return stack->arr[stack->top - 1];
    }
    fprintf(stderr, "Invalid Postfix Expression!\n");
    free_stack(stack);
    exit(EVAL_FAILED);
}
