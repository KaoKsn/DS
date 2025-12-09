// 3 - Infix to postfix conversion with an assumed left-to-right associativity.
// TODO: Handle multiple digit numbers.
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define FAILURE 1

typedef enum order {
    close = ')',
    open = '(',
    add = '+',
    sub = '-',
    mul = '*',
    div = '/',
    mod = '%',
} order;

int precedence(char op);

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./3infixToPostfix expression\n");
        return 1;
    } else if (argv[1] == NULL) {
        printf("Invalid input!\n");
        return 1;
    }
    int exprlen = strlen(argv[1]);
    if (exprlen == 0)
        return 1;

    char *expr = argv[1];
    printf("Infix: %s\n", expr);

    char stack[exprlen];
    int index = 0;
    printf("Postfix: ");
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isalnum(expr[i])) {
            printf("%c", expr[i]);
        }
        else {
            // If it is an open paranthesis, directly push, to avoid popping all the operators afterwards.
            if (expr[i] == open)
                stack[index++] = expr[i];
            // If it is a closing brace, pop until '(' is encountered.
            else if (expr[i] == close) {
                  while(stack[--index] != open)
                      printf("%c", stack[index]);  
            } else {
                while (precedence(expr[i]) < precedence(stack[index - 1])) {
                    printf("%c", stack[--index]); 
                }
                stack[index++] = expr[i];
            }
        }
    }
    // Pop any other operators left in the stack.
    while (index > -1) {
        printf("%c", stack[--index]);
    }
    printf("\n");
    return 0;
}

int precedence(char op)
{
    switch(op) {
        case close: return 3;
                    break;
        case mod:
        case mul:
        case div: return 2;
                  break;
        case add:
        case sub: return 1;
                  break;
        case open: return 0;
    }
}
