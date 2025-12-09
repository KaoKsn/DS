// 4 - Postfix evaluation assuming a valid input string is provided.
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define FAILURE 1

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./4evalulatePostfix expression\n");
        return 1;
    } else if (argv[1] == NULL) {
        printf("Invalid input!\n");
        return 1;
    }
    int exprlen = strlen(argv[1]);
    if (exprlen == 0)
        return 1;

    int stack[exprlen];
    int index = 0;
    for (int i = 0; argv[1][i] != '\0' && i < exprlen; i++) {
        // Ignore white spaces.
        if (argv[1][i] == ' ')
            continue;
        // Read the whole positive integer.
        else if (isdigit(argv[1][i])) {
            int n = 0;
            while (1) {
              n = n * 10 + argv[1][i] - '0';
              if (++i >= exprlen || argv[1][i] == ' ')
                  break;
              else if (isdigit(argv[1][i]) == 0) {
                  printf("Invalid Expression!\n");
                  return 1;
              }
            }
            stack[index++] = n;
        }
        else {
            // An opeartor must occur only when there are atleast 2 operands in the stack.
            if (index >= 2) {
                int op1 = stack[--index];
                int op2 = stack[--index];
                switch(argv[1][i]) {
                    case '+':
                              stack[index++] = op2 + op1;
                              break;
                    case '-':
                              stack[index++] = op2 - op1;
                              break;
                    case '*':
                              stack[index++] = op2 * op1;
                              break;
                    case '/':
                              if (op1 != 0)
                                  stack[index++] = op2 / op1;
                              else
                                  printf("Invalid expression!\n");
                              break;
                    case '%':
                              stack[index++] = op2 % op1;
                              break;
                    default:
                            fprintf(stderr, "Invalid operator encountered!\n");
                            return 1;
                }
            } else {
                  printf("Invalid Expression!\n");
                  return 1;
            }
        }
    }
    if (index == 1)
        printf("Result: %d\n", stack[--index]);
    else {
        fprintf(stderr, "Invalid expression!\n");
        return 1;
    }
    return 0;
}
