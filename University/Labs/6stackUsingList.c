// 6. Stack operations using singly linked list.
typedef struct Node {
  int val;
  struct Node *next;
} node_t;

void push(int value);
int pop();
void printStack();
void freeStack();

#include <stdio.h>
#include <stdlib.h>
#define INVALID_REQUEST 1

node_t *stack = NULL;

int main(void) {
    int choice, value;

    while (1) {
        printf("\n--- STACK MENU ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Print\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                printStack();
                break;
            case 4:
                printf("Exiting...\n");
                freeStack();
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// Building a list in the reverse order.
void push(int value)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
        return;
    node->val = value;
    // If the stack is empty.
    if (stack == NULL) {
        stack = node;
        node->next = NULL;
    } else {
        node->next = stack;
        stack = node;
    }
}

int pop()
{
    if (stack == NULL) {
        printf("Stack Empty!\n");
        return INVALID_REQUEST;
    }
    int returnVal = 0;
    node_t *tmp = stack;
    stack = stack->next;
    returnVal = tmp->val;
    printf("%d\n", returnVal);
    free(tmp);
    return returnVal;
}

void printStack()
{
  if (stack == NULL)
      return;

    printf("==== STACK ====\n");
    node_t *ptr = stack;
    while(ptr != NULL) {
        printf("%d\n", ptr->val);
        ptr = ptr->next;
    }
}
void freeStack()
{
    if (stack == NULL)
        return;

    node_t *ptr = stack;
    while(ptr != NULL) {
        node_t *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    stack = NULL;
    return;
}
